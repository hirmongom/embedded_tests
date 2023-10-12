/***************************************************************************************************
 * @file        main.c
 * 
 * @brief       Usart communication test program
 * 
 * @details     This programs pretends to test the usart functionality by performing a loopback on
 *              the USART1 peripheral
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

#include "sysclk_test.h"
#include "usart_test.h"

static uint8_t send_flag;

// Tx = PA9, Rx = PA10

//**************************************************************************************************
int main(void) {
  set_system_clock();
  usart1_init();

  RCC->AHB1ENR |= (1 << 2);       // Enable clock for GPIOC
  GPIOC->PUPDR |= (1 << 26);      // PC13 pull-down
  GPIOA->MODER |= (1 << 10);      // Set PA5 as output
  
  // EXTI line 13 for PC13 
  RCC->APB2ENR |= (1 << 14);        // Enable system configuration controller clock

  SYSCFG->EXTICR[3] &= ~(0xF << 4); // Clear register
  SYSCFG->EXTICR[3] |= (2 << 4);    // Select source input for the EXTI13
  
  EXTI->IMR |= (1 << 13);     // Unmask pin in EXTI line
  EXTI->FTSR &= ~(1 << 13); 
  EXTI->RTSR |= (1 << 13);    // Enable rising edge trigger

  NVIC->ISER[1] |= (1 << 8);  // Enable interrupt
  NVIC->IPR[40] |= (2 << 4);  // Set priority

  while(1) {
    if (send_flag == 1) {
      usart1_write_byte('A');
      send_flag = 0;

      for(int i = 0; i < 10000; i++);
      uint8_t c = usart1_read_byte();
      if (c == 'A') {
        GPIOA->ODR ^= (1 << 5);
      }
    }
  }
}


//**************************************************************************************************
void EXTI15_10_ISR(void) {
  if (EXTI->PR & (1 << 13)) {
    send_flag |= 1;
    EXTI->PR |= (1 << 13);    // Clear flag
  }
}


//**************************************************************************************************
void USART1_ISR(void) {
  GPIOA->ODR ^= (1 << 5);
  /*
  if (USART1->SR & (1 << 5)) {  // Check if RXNE (Read Data Register Not Empty) is set
    uint8_t received_char = (USART1->DR & 255);  // Read the data. This also clears the RXNE flag
    if (received_char == 'A') {
      GPIOA->ODR |= (1 << 5);
    } else { // Turn ON LED no matter what happens
      GPIOA->ODR |= (1 << 5);
    }
    
  } */
}