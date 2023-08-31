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


#define PLL_M       8         // Division factor for the main PLL (PLL) input clock
#define PLL_N       240       // Main PLL (PLL) multiplication factor for VCO
#define PLL_P       4         // Main PLL (PLL) division factor for main system clock
#define PLL_Q       5         // Main PLL (PLL) division factor for USB OTG FS, SDIO, and RNG.

#define APB1_CLK    15000000UL

void set_system_clock();
void start_clocks();
void user_gpio_init();
void usart2_init();
static inline void usart_write_byte(uint8_t byte);
static inline void usart_write_buffer(char *buffer, size_t length);
static inline uint8_t usart_read_byte();


//**************************************************************************************************
int main(void) {
  set_system_clock();
  start_clocks();
  user_gpio_init();
  usart2_init();

  while (1); // Infinite loop to prevent the program from exiting
}

//**************************************************************************************************
void set_system_clock() {
  // Target is 60MHz
  RCC->CR |= (1 << 16); // Enable HSE clock
  while(!(RCC->CR & (1 << 17)));  // Wait for HSE clock ready flag

  RCC->APB1ENR |= (1 << 28);  // Enable Power Interface clock
  
  PWR->CR |= (1 << 14);   // Scale 3 mode <= 64MHz 

  RCC->CFGR |= (0 << 7);    // (0b0xxx) AHB prescaler = system clock not divided  
  RCC->CFGR |= (5 << 10);   // (0b101) APB low speed prescaler = AHB / 4
  RCC->CFGR |= (4 << 13);   // (0b100) APB high speed prescaler = AHB / 2

  /* 
  * Configuring the PLL (Phase-Locked Loop) for the desired system clock:
  * 
  * 1. PLL_M: This value is directly set to the lowest bits [5:0] of the PLLCFGR register.
  *           It divides the input clock before it's fed to the VCO (Voltage-Controlled Oscillator).
  * 
  * 2. PLL_N: This value is shifted to the left by 6 bits and set to bits [14:6] of the PLLCFGR 
  *           register.
  *           It determines the multiplication factor for the VCO (Voltage-Controlled Oscillator).
  * 
  * 3. PLL_P: This value determines the division factor for the main system clock.
  *           The formula `((PLL_P >> 1) - 1)` is used to convert the actual division factor 
  *           (2, 4, 6, or 8) to the respective 2-bit representation in the PLLCFGR register.
  *           This value is then shifted to the left by 16 bits and set to bits [17:16].
  * 
  * 4. PLL_Q: This value is shifted to the left by 24 bits and set to bits [27:24] of the PLLCFGR 
  *           register.
  *           It determines the division factor for the USB OTG FS, SDIO, and RNG clocks.
  * 
  * 5. (1 << 22): This bit sets the PLL source to HSE (High-Speed External) clock. If this bit is 
  *               reset, then HSI (High-Speed Internal) is used as the PLL source.
  */
  RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (PLL_Q << 24) | (1 << 22);

  RCC->CR |= (1 << 24);   // Enable main PLL
  while (!(RCC->CR & (1 << 25)));   // Wait for PLL clock ready flag

/* Configure the Flash Access Control Register (ACR)
 * - (1 << 8): Prefetch enable. When set, it allows the Flash to fetch instructions before they are needed.
 * - (1 << 9): Instruction cache enable. When set, it caches recently used instructions to speed up execution.
 * - (1 << 10): Data cache enable. When set, it caches recently accessed data for faster access.
 * - (5 << 0): Sets the Flash latency to 5 wait states. This is the number of CPU cycles that the memory access instruction will stall until the data is fetched from Flash.
 */
  FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10 ) | (5 << 0);

  RCC->CFGR &= ~(3U << 0);    // Clear
	RCC->CFGR |= (2 << 0);    // Set PLL as system clock

  while(!(RCC->CFGR & (2 << 2)));   // Wait until PLL system clock status flag
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
  USART2->BRR = APB1_CLK / baud_rate; // Set the baud rate

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
  while (!(USART2->SR & (1 << 7))); // Wait for TXE flag to be set (Transmit data register empty)
  USART2->DR = byte;
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
    usart_write_byte('A');  // Send test character

    EXTI->PR |= (1 << 13);    // Clear flag
  }
}


//**************************************************************************************************
void USART2_ISR(void) {
  if (USART2->SR & (1 << 5)) {  // Check if RXNE (Read Data Register Not Empty) is set
    uint8_t received_char = (USART2->DR & 255);  // Read the data. This also clears the RXNE flag
    if (received_char == 'A') {
      GPIOA->ODR |= (1 << 5); // Toggle LED
    } else {
      GPIOA->ODR |= (1 << 5); // Toggle LED
    }
  }
}