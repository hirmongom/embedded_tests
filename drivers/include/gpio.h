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
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   02/07/2023
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

typedef enum {
  kModeInput,
  kModeOutput,
  kModeAlternate,
  kModeAnalog
} GpioMode;

typedef enum {
  kOtypePushPull,
  kOtypeOpenDrain
} GpioOutputType;

typedef enum {
  kSpeedLow,
  kSpeedMedium,
  kSpeedHigh,
  kSpeedVeryHigh
} GpioOutputSpeed;

typedef enum {
  kPullNone,
  kPullUp,
  kPullDown
} GpioPullType;

// TODO Configure port speed and such
// TODO Separate setup functions for output, analog or alternate funciton config
int gpioPinSetup(GPIO_Type *port, uint8_t pin, GpioMode mode);
int gpioPinPullTypeSetup(GPIO_Type *port, uint8_t pin, GpioPullType type);
int gpioPinRead(GPIO_Type *port, uint8_t pin, uint8_t *read);
int gpioPinWrite(GPIO_Type *port, uint8_t pin, uint8_t value, uint8_t *old_value);
int gpioPinToggle(GPIO_Type *port, uint8_t pin, uint8_t *old_value);