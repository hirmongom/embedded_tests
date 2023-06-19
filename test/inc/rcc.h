/**
 * @file        rcc.h
 * 
 * @brief       Header file for Reset and Clock Control (RCC) configuration
 * 
 * @details     This file defines the structure and constants for configuring
 *              and controlling the Reset and Clock Control (RCC) peripherals.
 * 
 * @see         RM0401 Reference Manual, Page 91 for more information on RCC configuration.
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

#ifndef RCC_H
#define RCC_H

#include <stdint.h>


/**
 * @brief       RCC register structure
 */
typedef struct {
    uint32_t CR;            // Clock control
    uint32_t PLLCFGR;       // PLL configuration
    uint32_t CFGR;          // Clock configuration
    uint32_t CIR;           // Clock interrupt
    uint32_t AHB1RSTR;      // AHB1 peripheral reset
    volatile const uint32_t RESERVED1[2];
    uint32_t APB1RSTR;      // APB1 peripheral reset
    uint32_t APB2RSTR;      // APB2 peripheral reset
    volatile const uint32_t RESERVED2;
    uint32_t AHB1ENR;       // AHB1 peripheral clock enable
    volatile const uint32_t RESERVED3[2];
    uint32_t APB1ENR;       // APB1 peripheral clock enable
    uint32_t APB2ENR;       // APB2 peripheral clock enable
    volatile const uint32_t RESERVED4;
    uint32_t AHB1LPENR;     // AHB1 peripheral clock enable in low power mode
    volatile const uint32_t RESERVED5[2];
    uint32_t APB1LPENR;     // APB1 peripheral clock enable in low power mode
    uint32_t APB2LPENR;     // APB2 peripheral clock enable in low power mode
    volatile const uint32_t RESERVED6;
    uint32_t BDCR;          // Backup domain control
    uint32_t CSR;           // Clock control & status
    volatile const uint32_t RESERVED7;
    uint32_t SSCGR;         // Spread spectrum clock generation
    volatile const uint32_t RESERVED8;
    uint32_t DCKCFGR;       // Dedicated Clocks Configuration
    volatile const uint32_t RESERVED9;
    uint32_t DCKCFGR2;      // Dedicated Clocks Configuration 2
} RCC_Type;

#define RCC_BASE_ADDR   0x40023800
#define RCC             ((RCC_Type*) RCC_BASE_ADDR)

#endif