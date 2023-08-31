/***************************************************************************************************
 * @file        usart.c
 * 
 * @brief       Source file for the USART2 peripheral
 * 
 * @details     This file implements the functions for initializing and using the USART2 peripheral.
 * 
 * @author      Hiram Montejano Gómez (hiram.montejano.gomez@gmail.com)
 * 
 * @date        Last Updated: 31/08/2023
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

void usart2_init(void) {
  RCC->AHB1ENR |= (1 << 0);   // Enable clock for GPIOA
  // @todo wait for flag?

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
  USART2->BRR = APB1_CLK / baud_rate; // Set the baud rate @todo APB1_CLK from sysclk.h

  USART2->CR1 |= (1 << 2);      // Usart receiver enable
  USART2->CR1 |= (1 << 3);      // Usart transmitter enable
  USART2->CR1 |= (1 << 13);     // Usart enable
}


void usart2_write_byte(uint8_t byte) {
  while (!(USART2->SR & (1 << 7))); // Wait for TXE flag to be set (Transmit data register empty)
  USART2->DR = byte;
}


void usart2_write_buffer(char *buffer, size_t length) {
  while (length-- > 0) usart_write_byte(*(uint8_t *)buffer++);
}


uint8_t usart2_read_byte(void) {
  return (uint8_t) (USART2->DR & 255);
}