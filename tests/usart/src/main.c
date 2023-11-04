/***************************************************************************************************
 * @file        main.c
 * 
 * @brief       Usart communication test program
 * 
 * @details     This programs pretends to test the usart functionality by performing a loopback on
 *              the USART2 peripheral
 * 
 * @author      Hiram Montejano Gómez (hiram.montejano.gomez@gmail.com)
 * 
 * @date        Last Updated: 29/09/2023
 * 
 * @note 				USART1_TX on PB6 (APB2)
 * 							USART1_RX on PB7 (APB2)
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

// #include "sysclk.h"
// #include "usart.h"

#define APB2_FREQ 16000000


/**************************************************************************************************/
int main(void) {
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
  USART1->BRR = APB2_FREQ / baud_rate; // @todo

  USART1->CR1 |= (1 << 2);      // Usart receiver enable
  USART1->CR1 |= (1 << 3);      // Usart transmitter enable

  USART1->CR1 |= (1 << 13);   	// Usart enable
}