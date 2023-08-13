/***************************************************************************************************
 * @file        stm32f410rb.h
 * @defgroup    stm32 stm32f410rb.h
 * 
 * @brief       Header file for STM32F410RB microcontroller peripherals.
 * 
 * @details     This file contains the structures and definitions for various peripherals
 *              on the STM32F410RB microcontroller. It provides an interface for configuring
 *              and accessing the peripherals such as GPIO, RCC, etc.
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   21/07/2023
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


/**
 * @defgroup    reg_def Macros
 * @ingroup     stm32
 */


/**
 * @defgroup    access_modifiers Access Modifiers
 * @ingroup     reg_def
 * @{
 */
#define     __I     volatile const    // Defines 'read only' permissions
#define     __O     volatile          // Defines 'write only' permissions
#define     __IO    volatile          // Defines 'read/write' permissions
/** @} */


/**
 * @defgroup    register_type Register Type Structs
 * @ingroup     stm32
 */


/***************************************************************************************************
 * @brief       SYSCFG register structure
 *
 * @details     This structure represents the SYSCFG register block, which contains
 *              configuration and control registers for various system functions.
 * 
 * @defgroup    syscfg_reg SYSCFG
 * @ingroup     register_type
 * @{
 */
typedef struct {
  __IO uint32_t MEMRMP;         /**< 0x00 (R/W) Memory remap */
  __IO uint32_t PMC;            /**< 0x04 (R/W) Peripheral mode configuration */
  __IO uint32_t EXTICR[4];      /**< 0x08-0x14 (R/W) External interrupt configuration [1..4] */
  __I  uint32_t RESERVED;
  __IO uint32_t CFGR2;          /**< 0x1C (R/W) Configuration register 2 */
  __IO uint32_t CMPCR;          /**< 0x20 (R/W) Compensation cell control */
  __IO uint32_t CFGR;           /**< 0x24 (R/W) Configuration register */
} SYSCFG_Type;
/** @} */


/***************************************************************************************************
 * @brief       EXTI register structure
 *
 * @details     This structure represents the EXTI register block, which is responsible for
 *              configuring and controlling the external interrupts.
 * 
 * @defgroup    exti_reg EXTI
 * @ingroup     register_type
 * @{
 */
typedef struct {
  __IO uint32_t IMR;            /**< 0x00 (R/W) Interrupt mask */
  __IO uint32_t EMR;            /**< 0x04 (R/W) Event mask */
  __IO uint32_t RTSR;           /**< 0x08 (R/W) Rising trigger selection */
  __IO uint32_t FTSR;           /**< 0x0C (R/W) Falling trigger selection */
  __IO uint32_t SWIER;          /**< 0x10 (R/W) Software interrupt event */
  __IO uint32_t PR;             /**< 0x14 (R/W) Pending */
} EXTI_Type;
/** @} */


/***************************************************************************************************
 * @brief       GPIO register structure
 *
 * @details     This structure represents the GPIO register block, which contains
 *              configuration and control registers for the General Purpose Input/Output pins.
 * 
 * @defgroup    gpio_reg  GPIO
 * @ingroup     register_type
 * @{
 */
typedef struct {
  __IO    uint32_t MODER;       /**< 0x00 (R/W) Mode */
  __IO    uint32_t OTYPER;      /**< 0x04 (R/W) Output type */
  __IO    uint32_t OSPEEDR;     /**< 0x08 (R/W) Output speed */
  __IO    uint32_t PUPDR;       /**< 0x0C (R/W) Pull-up/pull-down */
  __I     uint32_t IDR;         /**< 0x10 (R) Input data */
  __IO     uint32_t ODR;        /**< 0x14 (R/W) Output data */
  __IO    uint32_t BSRR;        /**< 0x18 (R/W) Bit set/reset */
  __IO    uint32_t LCKR;        /**< 0x1C (R/W) Configuration lock */
  __IO    uint32_t AFRL;        /**< 0x20 (R/W) Alternate function low */
  __IO    uint32_t AFRH;        /**< 0x24 (R/W) Alternate function high */
} GPIO_Type;
/** @} */


/***************************************************************************************************
 * @brief       RCC register structure
 *
 * @details     This structure represents the RCC register block, which contains
 *              configuration and control registers for the Reset and Clock Control.
 * 
 * @defgroup    rcc_reg RCC
 * @ingroup     register_type
 * @{
 */
typedef struct {
  __IO uint32_t CR;             /**< 0x00 (R/W) Clock control */
  __IO uint32_t PLLCFGR;        /**< 0x04 (R/W) PLL configuration */
  __IO uint32_t CFGR;           /**< 0x08 (R/W) Clock configuration */
  __IO uint32_t CIR;            /**< 0x0C (R/W) Clock interrupt */
  __IO uint32_t AHB1RSTR;       /**< 0x10 (R/W) AHB1 peripheral reset */
  __I  uint32_t RESERVED1[3];
  __IO uint32_t APB1RSTR;       /**< 0x20 (R/W) APB1 peripheral reset */
  __IO uint32_t APB2RSTR;       /**< 0x24 (R/W) APB2 peripheral reset */
  __I  uint32_t RESERVED2[2];
  __IO uint32_t AHB1ENR;        /**< 0x30 (R/W) AHB1 peripheral clock enable */
  __I  uint32_t RESERVED3[3];
  __IO uint32_t APB1ENR;        /**< 0x40 (R/W) APB1 peripheral clock enable */
  __IO uint32_t APB2ENR;        /**< 0x44 (R/W) APB2 peripheral clock enable */
  __I  uint32_t RESERVED4[2];
  __IO uint32_t AHB1LPENR;      /**< 0x50 (R/W) AHB1 peripheral clock enable in low power mode */
  __I  uint32_t RESERVED5[3];
  __IO uint32_t APB1LPENR;      /**< 0x60 (R/W) APB1 peripheral clock enable in low power mode */
  __IO uint32_t APB2LPENR;      /**< 0x64 (R/W) APB2 peripheral clock enable in low power mode */
  __I  uint32_t RESERVED6[2];
  __IO uint32_t BDCR;           /**< 0x70 (R/W) Backup domain control */
  __IO uint32_t CSR;            /**< 0x74 (R/W) Clock control & status */
  __I  uint32_t RESERVED7[2];
  __IO uint32_t SSCGR;          /**< 0x80 (R/W) Spread spectrum clock generation */
  __I  uint32_t RESERVED8[2];
  __IO uint32_t DCKCFGR;        /**< 0x8C (R/W) Dedicated Clocks Configuration */
  __I  uint32_t RESERVED9;
  __IO uint32_t DCKCFGR2;       /**< 0x94 (R/W) Dedicated Clocks Configuration 2 */
} RCC_Type;
/** @} */


/***************************************************************************************************
 * @brief       USART register structure
 * 
 * @details     This structure represents the USART register block, which contains
 *              configuration and control registers for the Universal Synchronous/Asynchronous 
 *              Receiver Transmitter
 * 
 * @defgroup    usart_reg USART
 * @ingroup     register_type
 * @{
 */
typedef struct {
  __I  uint32_t SR;             /**< 0x00 (R) Status */
  __IO uint32_t DR;             /**< 0x04 (R) Data */
  __IO uint32_t BRR;            /**< 0x08 (R/W) Baud rate */
  __IO uint32_t CR1;            /**< 0x0C (R/W) Control 1 */
  __IO uint32_t CR2;            /**< 0x10 (R/W) Control 2 */
  __IO uint32_t CR3;            /**< 0x14 (R/W) Control 3 */
  __IO uint32_t GTPR;           /**< 0x18 (R/W) Guard time and prescaler */
} USART_Type;
/** @} */


/***************************************************************************************************
 * @brief       NVIC register structure
 *
 * @details     This structure represents the NVIC register block, which contains
 *              configuration and control registers for the Nested Vectored Interrupt Controller.
 * 
 * @defgroup    nvic_reg NVIC
 * @ingroup     register_type
 * @{
 */
typedef struct {
  __IO uint32_t ISER[8];        /**< 0x000 (R/W) Interrupt set-enable */
  __I  uint32_t RESERVED1[24];
  __IO uint32_t ICER[8];        /**< 0x080 (R/W) Interrupt clear-enable */
  __I  uint32_t RESERVED2[24];
  __IO uint32_t ISPR[8];        /**< 0x100 (R/W) Interrupt set-pending */
  __I  uint32_t RESERVED3[24];
  __IO uint32_t ICPR[8];        /**< 0x180 (R/W) Interrupt clear-pending */
  __I  uint32_t RESERVED4[24];
  __IO uint32_t IABR[8];        /**< 0x200 (R/W) Interrupt active bit */
  __I  uint32_t RESERVED5[56];
  __IO uint8_t IPR[240];        /**< 0x300 (R/W) Interrupt priority */
  __I  uint32_t RESERVED6[644];
  __O  uint32_t STIR;           /**< 0xE00 (W) Software trigger interrupt */
} NVIC_Type;
/** @} */


/***************************************************************************************************
 * @defgroup    base_addr Register Base Addresses
 * @ingroup     reg_def
 * @{
 */
#define SYSCFG_BASE_ADDR    (0x40013800UL)
#define EXTI_BASE_ADDR      (0x40013C00UL)
#define GPIOA_BASE_ADDR     (0x40020000UL)
#define GPIOB_BASE_ADDR     (0x40020400UL)
#define GPIOC_BASE_ADDR     (0x40020800UL)
#define GPIOH_BASE_ADDR     (0x40021C00UL)
#define RCC_BASE_ADDR       (0x40023800UL)
#define USART1_BASE_ADDR    (0x40011000UL)
#define USART2_BASE_ADDR    (0x40004400UL)
#define USART6_BASE_ADDR    (0x40011400UL)
#define NVIC_BASE_ADDR      (0xE000E100UL)
/** @} */


/***************************************************************************************************
 * @defgroup    reg_map Register Structure Mapping
 * @ingroup     reg_def
 * @{
 */
#define SYSCFG              ((SYSCFG_Type*) SYSCFG_BASE_ADDR)
#define EXTI                ((EXTI_Type*)   EXTI_BASE_ADDR)
#define GPIOA               ((GPIO_Type*)   GPIOA_BASE_ADDR)
#define GPIOB               ((GPIO_Type*)   GPIOB_BASE_ADDR)
#define GPIOC               ((GPIO_Type*)   GPIOC_BASE_ADDR)
#define GPIOH               ((GPIO_Type*)   GPIOH_BASE_ADDR)
#define RCC                 ((RCC_Type*)    RCC_BASE_ADDR)
#define USART1              ((USART_Type*)  USART1_BASE_ADDR)
#define USART2              ((USART_Type*)  USART2_BASE_ADDR)
#define USART6              ((USART_Type*)  USART6_BASE_ADDR)
#define NVIC                ((NVIC_Type*)   NVIC_BASE_ADDR)
/** @} */


#endif