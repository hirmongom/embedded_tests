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
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   25/06/2023
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

int main(void) {
    
    RCC->AHB1ENR |= (1 << 0);       // Enable clock for GPIOA
    RCC->AHB1ENR |= (1 << 2);       // Enable clock for GPIOC
    GPIOA->MODER |= (1 << 10);      // Set PA5 as output
    GPIOC->MODER &= ~(1 << 26);     // Set PC13 as input (redundant)
    GPIOC->PUPDR |= (2 << 26);      // PC13 pull-down

    // Loop
    while (1) {
        GPIOA->ODR ^= (1 << 5);  // Toggle LED (PA5)  
        for (uint32_t i = 0; i < 1000000; i++);
        
        while (GPIOC->IDR & (1 << 13)) {
            GPIOA->ODR ^= (1 << 5);  // Toggle LED (PA5)  
            for (uint32_t i = 0; i < 100000; i++);
        }
    }

    return 0;
}