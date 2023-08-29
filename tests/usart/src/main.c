/***************************************************************************************************
 * @file        main.c
 * 
 * @brief       Usart communication test program
 * 
 * @details     This program demonstrates basic USART communication using USART2 on the STM32F410RB 
 *              microcontroller. The program configures the GPIO pins PA2 and PA3 as alternate 
 *              function mode to enable USART2 communication. It sets up USART2 with a specific 
 *              baud rate for serial communication.

 * @note        This program uses simple polling for data transmission, where it waits for the TXE 
 *              (Transmit Data Register Empty) flag to be set before sending each character. 
 *              For more robust USART communication in real-world applications, an interrupt-driven 
 *              or DMA-based approach is recommended.
 * 
 * @author      Hiram Montejano Gómez (hiram.montejano@gmail.com)
 * 
 * @date        Last Updated: 27/08/2023
 * 
 * @copyright   This file is part of the "STM32F10RB Microcontroller Applications" project.
 * 
 *              Every file is free software: you can redistribute it and/or modify
 *              it under the terms of the GNU General Public License as published by
 *              the Free Software Foundation, either version 3 of the License, or
 *              (at your option) any later version.
 * 
 *              These files are distributed in the hope that they will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *              GNU General Public License for more details.
 * 
 *              You should have received a copy of the GNU General Public License
 *              along with the "STM32F10RB Microcontroller Applications" project. If not, 
 *              see <http://www.gnu.org/licenses/>.
 */


#include <stdint.h>
#include <stddef.h>
#include "stm32f410rb.h"

#define FREQ 8000000    // 8MHz @todo need to manually set clock freq


void start_clocks();
void user_gpio_init();
void usart2_init();
static inline void usart_write_byte(uint8_t byte);
static inline void usart_write_buffer(char *buffer, size_t length);
static inline uint8_t usart_read_byte();


//**************************************************************************************************
int main(void) {
  start_clocks();
  user_gpio_init();
  usart2_init();

  while (1); // Infinite loop to prevent the program from exiting
}


//**************************************************************************************************
void start_clocks() {
  RCC->AHB1ENR |= (1 << 2);       // Enable clock for GPIOC
  RCC->AHB1ENR |= (1 << 0);       // Enable clock for GPIOA
  RCC->APB1ENR |= (1 << 17);      // Enable clock for USART2
  RCC->APB2ENR |= (1 << 14);      // Enable system configuration controller clock
}


//**************************************************************************************************
void user_gpio_init() {
  // User LED
  GPIOA->MODER |= (1 << 10);      // Set PA5 as output

  // User button
  GPIOC->MODER &= ~(3 << 26);     // Set PC13 as input (redundant)
  GPIOC->PUPDR &= ~(3 << 26);     // Reset
  GPIOC->PUPDR |= (1 << 26);      // PC13 pull-down

  // Interrupt configuration
  SYSCFG->EXTICR[3] &= ~(0xF << 4); // Clear register
  SYSCFG->EXTICR[3] |= (2 << 4);    // Select source input for the EXTI13
  
  EXTI->IMR |= (1 << 13);     // Unmask pin in EXTI line
  EXTI->FTSR &= ~(1 << 13); 
  EXTI->RTSR |= (1 << 13);    // Enable rising edge trigger

  NVIC->ISER[1] |= (1 << 8);  // Enable interrupt
  NVIC->IPR[40] |= (2 << 4);  // Set priority
}


//**************************************************************************************************
void user_led_init() {

}


//**************************************************************************************************
void usart2_init() {
  // USART2 GPIO Pins Configuration
  GPIOA->MODER |= (2 << 4);     // Alternate function mode on PA2
  GPIOA->MODER |= (2 << 6);     // Alternate function mode on PA3

  GPIOA->OSPEEDR |= (3 << 4);   // High speed
  GPIOA->OSPEEDR |= (3 << 6);   // High speed

  GPIOA->PUPDR &= ~(3 << 4);    // No pull-up, pull-down
  GPIOA->PUPDR &= ~(3 << 6);    // No pull-up, pull-down

  GPIOA->AFRL |= (7 << 8);      // Alternate Function 7 on PA2
  GPIOA->AFRL |= (7 << 12);     // Alternate Function 7 on PA3

  USART2->CR1 = 0;    // Disable this USART

  unsigned long baud_rate = 9600;
  USART2->BRR = FREQ / baud_rate; // Set the baud rate

  USART2->CR1 |= (1 << 2);      // Usart receiver enable
  USART2->CR1 |= (1 << 3);      // Usart transmitter enable

  // Configure receiver interrupt
  USART2->CR1 |= (1 << 5);    // RXNEIE = 1: RXNE interrupt enabled
  NVIC->ISER[1] |= (1 << 6);  // Enable interrupt for USART2 in NVIC
  NVIC->IPR[38] |= (1 << 4);  // Set priority

  USART2->CR1 |= (1 << 13);     // Usart enable
}


//**************************************************************************************************
static inline void usart_write_byte(uint8_t byte) {
  //while ((USART2->SR & (1 << 7)) == 0); // Wait for TXE flag to be set (Transmit data register empty)
  USART2->DR = byte;  // Send test character
}


//**************************************************************************************************
static inline void usart_write_buffer(char *buffer, size_t length) {
  while (length-- > 0) usart_write_byte(*(uint8_t *)buffer++);
}


//**************************************************************************************************
static inline uint8_t usart_read_byte() {
  return (uint8_t) (USART2->DR & 255);
}


//**************************************************************************************************
void EXTI15_10_ISR(void) {
  if (EXTI->PR & (1 << 13)) {
    while ((USART2->SR & (1 << 7)) == 0); // Wait for TXE flag to be set (Transmit data register empty)
    USART2->DR = 'A';  // Send test character

    EXTI->PR |= (1 << 13);    // Clear flag
  }
}


//**************************************************************************************************
void USART2_ISR(void) {
  if (USART2->SR & (1 << 5)) {  // Check if RXNE (Read Data Register Not Empty) is set
    uint8_t received_char = (USART2->DR & 255);  // Read the data. This also clears the RXNE flag
    if (received_char == 'A') {
      GPIOA->ODR ^= (1 << 5); // Toggle LED
    } else {
      GPIOA->ODR ^= (1 << 5); // Toggle LED
    }
  }
}