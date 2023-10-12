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
 * @date        Last Updated: 01/10/2023
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


void usart2_init(void);
void usart2_write(uint8_t ch);


//**************************************************************************************************
int main(void) {
  usart2_init();

  while (1) {
    usart2_write('A');
  }
}


//**************************************************************************************************
void usart2_init(void) {
  RCC->APB1ENR |= (1 << 17);
  RCC->AHB1ENR |= (1 << 0);
  GPIOA->AFRL |= (7 << 8);
  GPIOA->MODER |= (1 << 5);

  USART2->BRR = 16000000 / 9600;
  USART2->CR1 |= (1 << 3);
  USART2->CR1 |= (1 << 13);
}


//**************************************************************************************************
void usart2_write(uint8_t ch) {
  while (!(USART2->SR & (1 << 7)));
  USART2->DR = (ch & 0xFF);
}