/**
 * @file        stm32f410rb.h
 * 
 * @brief       Header file for STM32F410RB microcontroller peripherals.
 * 
 * @details     This file contains the structures and definitions for various peripherals
 *              on the STM32F410RB microcontroller. It provides an interface for configuring
 *              and accessing the peripherals such as GPIO, RCC, etc.
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

#ifndef STM32F410RB_H
#define STM32F410RB_H

#include <stdint.h>

#define     __I     volatile const       // Defines 'read only' permissions
#define     __O     volatile             // Defines 'write only' permissions
#define     __IO    volatile             // Defines 'read / write' permissions


// TODO missing comments
/****************************** SYSCFG ******************************/
/**
 * @brief       SYSCFG register structure
 */
typedef struct {
  __IO uint32_t MEMRMP;
  __IO uint32_t PMC;
  __IO uint32_t EXTICR[4];
  __IO uint32_t CFGR2;
  __IO uint32_t CMPCR;
  __IO uint32_t CFGR;
} SYSCFG_Type;


// TODO missing comments
/****************************** EXTI ******************************/
/**
 * @brief       EXTI register structure
 */
typedef struct {
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_Type;


/****************************** GPIO ******************************/
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


/****************************** RCC ******************************/
/**
 * @brief       RCC register structure
 */
typedef struct {
    __IO uint32_t CR;           // Clock control
    __IO uint32_t PLLCFGR;      // PLL configuration
    __IO uint32_t CFGR;         // Clock configuration
    __IO uint32_t CIR;          // Clock interrupt
    __IO uint32_t AHB1RSTR;     // AHB1 peripheral reset
    __I  uint32_t RESERVED1[3];
    __IO uint32_t APB1RSTR;     // APB1 peripheral reset
    __IO uint32_t APB2RSTR;     // APB2 peripheral reset
    __I  uint32_t RESERVED2[2];
    __IO uint32_t AHB1ENR;      // AHB1 peripheral clock enable
    __I  uint32_t RESERVED3[3];
    __IO uint32_t APB1ENR;      // APB1 peripheral clock enable
    __IO uint32_t APB2ENR;      // APB2 peripheral clock enable
    __I  uint32_t RESERVED4[2];
    __IO uint32_t AHB1LPENR;    // AHB1 peripheral clock enable in low power mode
    __I  uint32_t RESERVED5[3];
    __IO uint32_t APB1LPENR;    // APB1 peripheral clock enable in low power mode
    __IO uint32_t APB2LPENR;    // APB2 peripheral clock enable in low power mode
    __I  uint32_t RESERVED6[2];
    __IO uint32_t BDCR;         // Backup domain control
    __IO uint32_t CSR;          // Clock control & status
    __I  uint32_t RESERVED7[2];
    __IO uint32_t SSCGR;        // Spread spectrum clock generation
    __I  uint32_t RESERVED8[2];
    __IO uint32_t DCKCFGR;      // Dedicated Clocks Configuration
    __I  uint32_t RESERVED9;
    __IO uint32_t DCKCFGR2;     // Dedicated Clocks Configuration 2
} RCC_Type;


/****************************** NVIC ******************************/
/**
 * @brief       NVIC register structure
 */
typedef struct {
  __IO uint32_t ISER[3];        // Interrupt set-enable
  __I  uint32_t RESERVED1[5];
  __IO uint32_t ICER[3];        // Interrupt clear-enable
  __I  uint32_t RESERVED2[5];
  __IO uint32_t ISPR[3];        // Interrupt set-pending
  __I  uint32_t RESERVED3[5];
  __IO uint32_t ICPR[3];        // Interrupt clear-pending
  __I  uint32_t RESERVED4[5];
  __IO uint32_t IABR[3];        // Interrupt active bit
  __I  uint32_t RESERVED5[5];
  __IO uint32_t IPR[60];        // Interrupt priority 
  __I  uint32_t RESERVED6[5];
  __O  uint32_t STIR;           // Software trigger interrupt
} NVIC_Type;


/********************* Peripheral Memory Map ********************/

#define SYSCFG_BASE_ADDR    (0x40013800UL)
#define EXTI_BASE_ADDR      (0x40013C00UL)
#define GPIOA_BASE_ADDR     (0x40020000UL)
#define GPIOB_BASE_ADDR     (0x40020400UL)
#define GPIOC_BASE_ADDR     (0x40020800UL)
#define GPIOH_BASE_ADDR     (0x40021C00UL)
#define RCC_BASE_ADDR       (0x40023800UL)
#define NVIC_BASE_ADDR      (0xE000E100UL)


/********************* Peripheral Declaration ********************/

#define SYSCFG              ((SYSCFG_Type*) SYSCFG_BASE_ADDR)
#define EXTI                ((EXTI_Type*) EXTI_BASE_ADDR)
#define GPIOA               ((GPIO_Type*) GPIOA_BASE_ADDR)
#define GPIOB               ((GPIO_Type*) GPIOB_BASE_ADDR)
#define GPIOC               ((GPIO_Type*) GPIOC_BASE_ADDR)
#define GPIOH               ((GPIO_Type*) GPIOH_BASE_ADDR)
#define RCC                 ((RCC_Type*) RCC_BASE_ADDR)
#define NVIC                ((NVIC_Type*) NVIC_BASE_ADDR)

#endif