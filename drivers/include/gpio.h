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
 * @todo        Need higher abstraction
 *              Doxygen comment blocks
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   25/06/2023
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
#include <stddef.h>

typedef enum {
  kPortA,
  kPortB,
  kPortC,
  kPortH
} GpioPort;

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

typedef struct {
  uint8_t *pins;
  uint8_t n_pins;
  GpioMode mode;
  GpioOutputType output_type;
  GpioOutputSpeed output_speed;
  GpioPullType pull_type;
} GpioPinConfig;

#define GPIO_PIN_CONFIG_DEFAULT     { .pins = NULL, .n_pins = 0, .mode = 0, .output_type = 0, .output_speed = 0, .pull_type = 0 }
#define GPIO_MAX_PINS               16

int InitializeGpioPort(GpioPort port);
int ConfigureGpioPin(GpioPort port, GpioPinConfig *config);
int ToggleOutputGpioPin(GpioPort port, uint8_t pin);