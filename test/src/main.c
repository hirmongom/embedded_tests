/**
 * @file        main.c
 * 
 * @brief       
 *
 * @details     
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

#include "stm32f410rb.h"

int not_working_main(void) {
    
    RCC->AHB1ENR |= (1 << 0);       // Enable clock for GPIOA

    GPIOA->MODER |= (1 << 10);     // Set PA5 as output

    // Loop
    while (1) {
        GPIOA->ODR ^= (1 << 5);  // Turn on LED (PA5)  
        for (int i = 0; i < 1000000; i++);
    }

    return 0;
}

int main(void)
{
    *RCC_AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN);

    // do two dummy reads after enabling the peripheral clock, as per the errata
    volatile uint32_t dummy;
    dummy = *(RCC_AHB1ENR);
    dummy = *(RCC_AHB1ENR);

    *GPIOA_MODER |= (1 << GPIO_MODER_MODER5);
    
    while(1)
    {
        *GPIOA_ODR ^= (1 << LED_PIN);
        for (uint32_t i = 0; i < 1000000; i++);
    }

    return 0;
}