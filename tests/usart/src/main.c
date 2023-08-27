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
#include "stm32f410rb.h"


void start_clocks();
void user_button_init();
void user_led_init();


//**************************************************************************************************
int main(void) {
  start_clocks();
  user_button_init();
  user_led_init();
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
void user_button_init() {
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
  NVIC->IPR[40] |= (1 << 4);  // Set priority
}


//**************************************************************************************************
void user_led_init() {
  GPIOA->MODER |= (1 << 10);      // Set PA5 as output
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

  /*
  * USART2 is in the APB1, the clock source is pclk1
  * pclk1 = hclk / 2
  * hclk derives from the system clock (with no preescalers configured in this case)
  * the mcu resets to the HSI clock (dont know how to change clock sources yet)
  * HSI operates at 16MHz
  * therefore, pclk1 = 8MHz
  */
  uint32_t system_core_clock = 8000000;  // USART clock is 8MHz
  uint16_t baud_rate = 9600;

  uint16_t mantissa = system_core_clock / (16 * baud_rate);
  uint16_t fraction = (system_core_clock % (16 * baud_rate)) / baud_rate;

  USART2->BRR = (mantissa << 4) | fraction; // Set the baud rate
  USART2->CR2 &= ~(3 << 12);    // 1 Stop bit
  USART2->CR3 &= ~(1 << 3);     // Half duplex mode not selected
  USART2->CR1 |= (1 << 2);      // Usart receiver enable
  USART2->CR1 |= (1 << 3);      // Usart receiver enable
  USART2->CR1 |= (1 << 13);     // Usart enable
}


//**************************************************************************************************
void EXTI15_10_ISR(void) {
  if (EXTI->PR & (1 << 13)) {
    char data[] = "a"; //"Hello USART"; // Use an array of characters to store the string
  
    for (unsigned long i = 0; i < sizeof(data) - 1; i++) {
      while (!(USART2->SR & (1 << 7))); // Wait for TXE flag to be set
      USART2->DR = data[i];     // Send one character at a time
      USART2->CR1 |= (1 << 0);  // Send break
      while (!(USART2->SR & (1 << 6))); // Wait for TC flag (transmission complete)
    }

    EXTI->PR |= (1 << 13);    // Clear flag
    }
}