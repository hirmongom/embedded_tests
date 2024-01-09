/***************************************************************************************************
 * @file        usart.c
 * 
 * @brief       Source file for the USART2 peripheral
 * 
 * @details     This file implements the functions for initializing and using the USART2 peripheral.
 * 
 * @author      Hiram Montejano Gómez (hiram.montejano.gomez@gmail.com)
 * 
 * @date        Last Updated: 11/11/2023
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
#include "sysclk.h"
#include "usart.h"


/**************************************************************************************************/
void usart2_init(void) {
  RCC->AHB1ENR |= (1 << 0);   // Enable clock for GPIOA

  // USART2 GPIO Pins Configuration
  GPIOA->MODER |= (2 << 4);     // Alternate function mode on PA2
  GPIOA->MODER |= (2 << 6);     // Alternate function mode on PA3

  GPIOA->OSPEEDR |= (3 << 4);   // High speed
  GPIOA->OSPEEDR |= (3 << 6);   // High speed

  GPIOA->PUPDR &= ~(3 << 4);    // No pull-up, pull-down
  GPIOA->PUPDR &= ~(3 << 6);    // No pull-up, pull-down

  GPIOA->AFRL |= (7 << 8);      // Alternate Function 7 on PA2 (Tx)
  GPIOA->AFRL |= (7 << 12);     // Alternate Function 7 on PA3 (Rx)

  USART2->CR1 = 0;    // Disable this USART

  unsigned long baud_rate = 9600;
  USART2->BRR = APB1_FREQ / baud_rate;

  USART2->CR1 |= (1 << 2);      // Usart receiver enable
  USART2->CR1 |= (1 << 3);      // Usart transmitter enable

  // Configure receiver interrupt
  USART2->CR1 |= (1 << 5);    // RXNEIE = 1: RXNE interrupt enabled
  NVIC->ISER[1] |= (1 << 6);  // Enable interrupt for USART2 in NVIC
  NVIC->IPR[38] |= (1 << 4);  // Set priority

  USART2->CR1 |= (1 << 13);   // Usart enable
}


/**************************************************************************************************/
void usart2_write_byte(uint8_t byte) {
  while (!(USART2->SR & (1 << 7))); // Wait for TXE flag to be set (Transmit data register empty)
  USART2->DR = byte;
}


/**************************************************************************************************/
void usart2_write_buffer(char *buffer, size_t length) {
  while (length-- > 0) usart2_write_byte(*(uint8_t *)buffer++);
}


/**************************************************************************************************/
uint8_t usart2_read_byte(void) {
  while (!(USART2->SR & (1 << 5))); // Wait for RXNE flag to be set (Data is ready to be read)
  return (uint8_t) (USART2->DR & 255);
}


/**************************************************************************************************/
void usart1_init(void) {
	RCC->APB2ENR |= (1 << 4);			// Enable Clock for USART 1
	RCC->AHB1ENR |= (1 << 1);			// Enable Clock for GPIOB

	GPIOB->MODER |= (2 << 12);		// Enable Alternate function on PB6
	GPIOB->MODER |= (2 << 14);		// Enable Alternate function on PB7

	GPIOB->OSPEEDR |= (3 << 12);	// Set output to very high speed on PB6
	GPIOB->OSPEEDR |= (3 << 14);	// Set output to very high speed on PB7

	GPIOB->AFRL |= (7 << 24);			// Enable USART1_TX AF on PB6	
	GPIOB->AFRL |= (7 << 28);			// Enable USART1_RX AF on PB7

	USART1->CR1 = (0 << 13);    	// Usart disable

	unsigned long baud_rate = 9600;
	USART1->BRR = APB2_FREQ / baud_rate;

	USART1->CR1 |= (1 << 2);      // Usart receiver enable
	USART1->CR1 |= (1 << 3);      // Usart transmitter enable

	USART1->CR1 |= (1 << 13);   	// Usart enable
}


/**************************************************************************************************/
void usart1_write_byte(uint8_t byte) {
	while (!(USART1->SR & (1 << 7)));
	USART1->DR = byte;
}


/**************************************************************************************************/
void usart1_write_buffer(char *buffer, size_t length) {
	while (length-- > 0) usart1_write_byte(*(uint8_t *)buffer++);
}


/**************************************************************************************************/
uint8_t usart1_read_byte(void) {
	while (!(USART1->SR & (1 << 5))); // Wait for RXNE flag to be set (Data is ready to be read)
  return (uint8_t) (USART1->DR & 255);
}