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
 * @date        Last Updated:   19/06/2023
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

#ifndef STM32F410RB_H
#define STM32F410RB_H

#include <stdint.h>

#define     __I     volatile const       // Defines 'read only' permissions
#define     __O     volatile             // Defines 'write only' permissions
#define     __IO    volatile             // Defines 'read / write' permissions


/******************************RCC******************************/
/**
 * @brief       RCC register structure
 */
typedef struct {
    __IO uint32_t CR;           // Clock control
    __IO uint32_t PLLCFGR;      // PLL configuration
    __IO uint32_t CFGR;         // Clock configuration
    __IO uint32_t CIR;          // Clock interrupt
    __IO uint32_t AHB1RSTR;     // AHB1 peripheral reset
    __I RESERVED1[2];
    __IO uint32_t APB1RSTR;     // APB1 peripheral reset
    __IO uint32_t APB2RSTR;     // APB2 peripheral reset
    __I RESERVED2;
    __IO uint32_t AHB1ENR;      // AHB1 peripheral clock enable
    __I RESERVED3[2];
    __IO uint32_t APB1ENR;      // APB1 peripheral clock enable
    __IO uint32_t APB2ENR;      // APB2 peripheral clock enable
    __I RESERVED4;
    __IO uint32_t AHB1LPENR;    // AHB1 peripheral clock enable in low power mode
    __I RESERVED5[2];
    __IO uint32_t APB1LPENR;    // APB1 peripheral clock enable in low power mode
    __IO uint32_t APB2LPENR;    // APB2 peripheral clock enable in low power mode
    __I uint32_t RESERVED6;
    __IO uint32_t BDCR;         // Backup domain control
    __IO uint32_t CSR;          // Clock control & status
    __I uint32_t RESERVED7;
    __IO uint32_t SSCGR;        // Spread spectrum clock generation
    __I uint32_t RESERVED8;
    __IO uint32_t DCKCFGR;      // Dedicated Clocks Configuration
    __I uint32_t RESERVED9;
    __IO uint32_t DCKCFGR2;     // Dedicated Clocks Configuration 2
} RCC_Type;

/******************************GPIOA******************************/
/**
 * @brief       GPIO register structure
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


/*************************Memory Map************************/

#define RCC_BASE_ADDR       0x40023800
#define RCC                 ((RCC_Type*) RCC_BASE_ADDR)

#define GPIOA_BASE_ADDR     0x40020000UL
#define GPIOB_BASE_ADDR     0x40020400UL
#define GPIOC_BASE_ADDR     0x40020800UL
#define GPIOA               ((GPIO_Type*) GPIOA_BASE_ADDR)
#define GPIOB               ((GPIO_Type*) GPIOB_BASE_ADDR)
#define GPIOC               ((GPIO_Type*) GPIOC_BASE_ADDR)

#endif