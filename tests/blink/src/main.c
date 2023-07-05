/**
 * @file        main.c
 * 
 * @brief       LED Blinking Application
 *
 * @details     This file contains a simple program to blink an LED connected 
 *              to Pin PA5 of the STM32F10RB microcontroller.
 *              The led blinks rapidly while the user button is not pressed.
 *              If the user button is pressed, the blinking speed lowers until the
 *              button is released
 * 
 * @note        This program utilizes the Nucleo board's built-in user LED and user button, 
 *              which are connected to PA5 and PC13, respectively.
 *
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   05/07/2023
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

#include "stm32f410rb.h"

void EXTI15_10_ISR(void);

int main(void) {
    
    RCC->AHB1ENR |= (1 << 0);       // Enable clock for GPIOA
    RCC->AHB1ENR |= (1 << 2);       // Enable clock for GPIOC
    GPIOA->MODER |= (1 << 10);      // Set PA5 as output
    GPIOC->MODER &= ~(1 << 26);     // Set PC13 as input (redundant)
    GPIOC->PUPDR |= (2 << 26);      // PC13 pull-down

    // EXTI line 13 for PC13
    RCC->APB2ENR |= (1 << 14);    // Enable system configuration controller clock
    SYSCFG->EXTICR[4] &= ~(0xF << 4); // Clear register
    SYSCFG->EXTICR[4] |= (2 << 4);  // Select source input for the EXTI13
    
    EXTI->IMR |= (1 << 13); // Set pin in EXTI line as interrupt
    EXTI->RTSR &= ~(1 << 13); // Enable rising edge trigger
    EXTI->FTSR |= (1 << 13);

    /* TODO INTERRUPT CONFIGURATION CRASHES BLINK */
    NVIC->IPR[10] |= (0x3 << 4);
    NVIC->ISER[1] |= (1 << 8);  // Enable interrupt
    
    // Loop
    while (1) {
        GPIOA->ODR ^= (1 << 5);  // Toggle LED (PA5)  
        for (uint32_t i = 0; i < 100000; i++);
    }

    return 0;
}

void EXTI15_10_ISR(void) {
  if (EXTI->PR & (1 << 13)) {
    EXTI->PR |= (1 << 13);
    for (uint32_t i = 0; i < 10000000; i++);
  }
}