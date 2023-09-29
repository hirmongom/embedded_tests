/***************************************************************************************************
 * @file        usart.c
 * 
 * @brief       Source file for the USART2 peripheral
 * 
 * @details     This file implements the functions for initializing and using the USART2 peripheral.
 * 
 * @author      Hiram Montejano Gómez (hiram.montejano.gomez@gmail.com)
 * 
 * @date        Last Updated: 02/09/2023
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
#include "sysclk_test.h"
#include "usart_test.h"


void usart1_init(void) {
  RCC->AHB1ENR |= (1 << 0);   // Enable clock for GPIOA

  // USART2 GPIO Pins Configuration
  GPIOA->MODER |= (2 << 18);     // Alternate function mode on PA9
  GPIOA->MODER |= (2 << 20);     // Alternate function mode on PA10

  GPIOA->OSPEEDR |= (3 << 4);   // High speed
  GPIOA->OSPEEDR |= (3 << 6);   // High speed

  GPIOA->AFRH |= (7 << 4);      // Alternate Function 7 on PA9 (Tx)
  GPIOA->AFRH |= (7 << 8);     // Alternate Function 7 on PA10 (Rx)

  USART1->CR1 = 0;    // Disable this USART

  unsigned long baud_rate = 9600;
  USART1->BRR = APB1_FREQ / baud_rate;

  USART1->CR1 |= (1 << 2);      // Usart receiver enable
  USART1->CR1 |= (1 << 3);      // Usart transmitter enable

  // Configure receiver interrupt
  USART2->CR1 |= (1 << 5);    // RXNEIE = 1: RXNE interrupt enabled
  NVIC->ISER[1] |= (1 << 5);  // Enable interrupt for USART2 in NVIC
  NVIC->IPR[37] |= (1 << 4);  // Set priority

  USART1->CR1 |= (1 << 13);   // Usart enable
}


void usart1_write_byte(uint8_t byte) {
  while (!(USART1->SR & (1 << 7))); // Wait for TXE flag to be set (Transmit data register empty)
  USART1->DR = byte;
}


void usart1_write_buffer(char *buffer, size_t length) {
  while (length-- > 0) usart1_write_byte(*(uint8_t *)buffer++);
}


uint8_t usart1_read_byte(void) {
  while (!(USART1->SR & (1 << 5))); // Wait for RXNE flag to be set (Data is ready to be read)
  return (uint8_t) (USART1->DR & 255);
}