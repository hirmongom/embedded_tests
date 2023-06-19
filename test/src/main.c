/**
 * @file        main.c
 * 
 * @brief       GPIO Button and LED Control
 * 
 *              This code initializes GPIO ports, configures a button on PC13, and controls 
 *              a LED on PA5.
 *              While the button is pressed, the LED is turned on, and when the button is 
 *              released, the LED is turned off.
 *
 * @details     The code performs the following steps:
 *                  1. Initializes the clock for the GPIO ports.
 *                  2. Configures GPIOA (PA5) as an output pin for the LED and GPIOC (PC13) 
 *                      as an input pin for the button.
 *                  3. Implements a main loop that continuously checks the state of the button.
 *                      - While the button is pressed (PC13 is high), 
 *                          the LED is turned on (PA5 is set high).
 *                      - While the button is released (PC13 is low), 
 *                          the LED is turned off (PA5 is set low)
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   17/06/2023
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

#include "gpio.h"
#include "rcc.h"

int main(void) {
    
    RCC->AHB1ENR |= (1 << 0);       // Enable clock for GPIOA
    RCC->AHB1RSTR |= (1 << 0);      // Reset GPIOA
    GPIOA->MODER &= ~(2 << 10);     // Set PA5 as output
    GPIOA->OTYPER &= ~(1 << 4);     // Set PA5 as output push-pull (redundant)

    // Loop
    while (1) {
        GPIOA->ODR ^= (1 << 5);  // Turn on LED (PA5)  
        for (int i = 0; i < 1000000; i++);
    }

    return 0;
}