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
 * @date        Last Updated: 30/07/2023
 * 
 * @todo        With interrupts
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

int main(void) {
  /* Configure GPIO pins */
  RCC->AHB1ENR |= (1 << 0);     // Enable clock for GPIOA
  
  GPIOA->MODER |= (2 << 4);     // Alternate function mode on PA2
  GPIOA->MODER |= (2 << 6);     // Alternate function mode on PA3

  GPIOA->AFRL |= (7 << 8);      // Alternate Function 7 on PA2
  GPIOA->AFRL |= (7 << 12);      // Alternate Function 7 on PA3

  /* Configure USART2 on PA2 and PA3 */
  RCC->APB1ENR |= (1 << 17);    // Enable clock for USART2

  uint32_t system_core_clock = 16000000;
  uint16_t baud_rate = 9600;
  uint16_t usart_div = (uint16_t) system_core_clock / baud_rate;

  USART2->BRR = ((usart_div / 16) << 4) | (usart_div % 16);   // Set baud rate

  USART2->CR1 |= (1 << 3);  // Usart transmitter enable

  /* Test program */
  char data[] = "Hi"; // Use an array of characters to store the string
  
  for (int i = 0; i < 2; i++) {
    while (!(USART2->SR & (1 << 7))); // Wait for TXE flag to be set
    USART2->DR = data[i]; // Send one character at a time
  }

  while (!(USART2->SR & (1 << 6))); // Wait for TC flag (transmission complete)

  while (1); // Infinite loop to prevent the program from exiting
} 