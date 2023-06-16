/**
 * @file        gpio.h
 * 
 * @brief       Header file for General-purpose I/Os (GPIO) configuration
 * 
 * @details     This file defines the structure and functions for configuring 
 *              and controlling the General-Purpose I/Os (GPIO) peripherals.
 * 
 * @see         RM0401 Reference Manual, Page 135 for more information on GPIO configuration.
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   16/06/2023
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

#define     __I     volatile const       // Defines 'read only' permissions
#define     __O     volatile             // Defines 'write only' permissions
#define     __IO    volatile             // Defines 'read / write' permissions

/**
 * @brief       GPIO register structure
 * 
 *              This structure defines the layout of the GPIO registers.
 */
typedef struct {
    __IO    uint32_t MODER;     // Mode
    __IO    uint32_t OTYPER;    // Output type
    __IO    uint32_t OSPEEDR;   // Output speed
    __IO    uint32_t PUPDR;     // Pull-up/pull-down
    __I     uint32_t IDR;       // Input data
    __O     uint32_t ODR;       // Output data
    __IO    uint32_t BSRR;      // Bit set/reset
    __IO    uint32_t LCKR;      // Configuration lock
    __IO    uint32_t AFRL;      // Alternate function low
    __IO    uint32_t AFRH;      // Alternate function high
} GPIO_Type;

#define GPIOA_BASE_ADDR     0x40020000UL
#define GPIOB_BASE_ADDR     0x40020400UL
#define GPIOC_BASE_ADDR     0x40020800UL

#define GPIOA               ((GPIO_Type*)) GPIOA_BASE_ADDR
#define GPIOB               ((GPIO_Type*)) GPIOB_BASE_ADDR
#define GPIOC               ((GPIO_Type*)) GPIOC_BASE_ADDR

/**
 * @brief       Initialize GPIOs
 * 
 *              This function initializes the GPIOs by configuring their mode, output type, 
 *              output speed, and pull-up/pull-down settings.
 *              Call this function before using the GPIOs.
 * 
 * @warning     It is still not implemented
 */
void GPIO_Init(void);   // Temporary