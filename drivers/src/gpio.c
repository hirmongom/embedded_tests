/**
 * @file        gpio.h
 * 
 * @brief       Source file for GPIO peripheral driver.
 * 
 * @details     This file implements the functions for configuring and controlling GPIO pins
 *              on the STM32F10RB microcontroller.
 * 
 * @see         RM0401 Reference Manual, Page 135 for more information on GPIO configuration.
 * 
 * @note        This file will grow as I keep finding more needs and adding functionality
 * 
 * @warning     Untested
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   24/06/2023
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

#include "gpio.h"
#include "stm32f410rb.h"

static uint8_t initializedPorts[4];

// TODO manage errors kinda like POSIX

int GPIO_Init(GPIO_Port port) {
    if (port >= 4) return 1;    // Invalid port
    if (initializedPorts[port] == 1) return 1;  // Port already initialized

    switch (port) {
        case GPIO_PORT_A:
            RCC->AHB1ENR |= (1 << 0);
            break;
        case GPIO_PORT_B:
            RCC->AHB1ENR |= (1 << 1);
            break;
        case GPIO_PORT_C:
            RCC->AHB1ENR |= (1 << 2);
            break;
        case GPIO_PORT_H:
            RCC->AHB1ENR |= (1 << 7);
            break;
        default:
            return 1;   // Invalid port
            break;
    }

    // TODO make the delay more accurate
    // Wait for clock stabilization
    for (volatile uint32_t delay = 0; delay < 100000; ++delay) {
        // Delay loop
    }

    initializedPorts[port] = 1;
    return 0;
}

int GPIO_Pin_Configure(GPIO_Port port, GPIO_PIN_Config *config) {
    if (initializedPorts[port] == 0) return 1;      // Port is not initialized
    if (config->pins == NULL) return 1;  // Invalid pins array

    GPIO_Type *gpioPort;
    switch (port) {
        case GPIO_PORT_A:
            gpioPort = GPIOA;
            break;
        case GPIO_PORT_B:
            gpioPort = GPIOB;
            break;
        case GPIO_PORT_C:
            gpioPort = GPIOC;
            break;
        case GPIO_PORT_H:
            gpioPort = GPIOH;
            break;
        default:
            return 1;      // Wrong port
            break;
    }

    for (int i = 0; i < config->nPins; i++) {
        gpioPort->MODER     |=  (config->mode   << (config->pins[i] * 2));    // Set mode
        gpioPort->OTYPER    |=  (config->otype  << config->pins[i]);        // Set output type
        gpioPort->OSPEEDR   |=  (config->ospeed << (config->pins[i] * 2));    // Set output speed
        gpioPort->PUPDR     |=  (config->pull   << (config->pins[i] * 2));    // Set pull type
    }
    
    return 0;
}