/**
 * @file        gpio.h
 * 
 * @brief       Header file for GPIO peripheral driver.
 * 
 * @details     This file provides the necessary definitions and functions for configuring 
 *              and controlling GPIO pins on the STM32F10RB microcontroller.
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

typedef enum {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_H
} GPIO_Port;

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG
} GPIO_Mode;

typedef enum {
    GPIO_OTYPE_PUSH_PULL,
    GPIO_OTYPE_OPEN_DRAIN
} GPIO_OutputType;

typedef enum {
    GPIO_SPEED_LOW,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH,
    GPIO_SPEED_VERY_HIGH
} GPIO_OutputSpeed;

typedef enum {
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} GPIO_PullType;

typedef struct {
    uint8_t *pins;
    uint8_t nPins;
    GPIO_Mode mode;
    GPIO_OutputType otype;
    GPIO_OutputSpeed ospeed;
    GPIO_PullType pull;
} GPIO_Pin_Config;

#define GPIO_PIN_CONFIG_DEFAULT     { .pins = NULL, .nPins = 0, .mode = 0, .otype = 0, .ospeed = 0, .pull = 0 }
#define GPIO_MAX_PINS               16

int GPIO_Init(GPIO_Port port);
int GPIO_Pin_Configure(GPIO_Port port, GPIO_Pin_Config *config);