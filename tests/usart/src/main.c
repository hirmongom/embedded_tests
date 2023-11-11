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
 * @date        Last Updated: 11/11/2023
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

#include "sysclk.h"
#include "usart.h"


/**************************************************************************************************/
int main(void) {
	set_system_clock();
	usart1_init();

	RCC->AHB1ENR |= (1 << 0);       // Enable clock for GPIOA
	GPIOA->MODER |= (1 << 10);      // Set PA5 as output

	int num = 0;
	while (1) {
		num = (num + 1) % 10;
		for (int i = 0; i < 1000000; i++);
		usart1_write_byte(num);
		for (int i = 0; i < 1000000; i++);
		if (usart1_read_byte() == 1) {
			GPIOA->ODR ^= (1 << 5);
		}
	}
}