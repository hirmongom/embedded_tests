/***************************************************************************************************
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
 * @date        Last Updated:   15/07/2023
 * 
 * @todo        Functions for Analog or Afsel
 * @todo        Output type configuration
 * @todo        Output speed configuration
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


/***************************************************************************************************
 * @brief       GPIO mode options.
 *
 * @details     This enumeration defines the available modes for GPIO pins.
 *              The modes determine the general purpose and behavior of the pins.
 */
typedef enum {
  kModeInput,          /**< Input mode. */
  kModeOutput,         /**< Output mode. */
  kModeAlternate,      /**< Alternate function mode. */
  kModeAnalog          /**< Analog mode. */
} GpioMode;


/***************************************************************************************************
 * @brief       GPIO output type options.
 *
 * @details     This enumeration defines the available output types for GPIO pins.
 *              The output types determine the behavior of the pins when driving an output signal.
 */
typedef enum {
  kOtypePushPull,      /**< Push-pull output type. */
  kOtypeOpenDrain      /**< Open-drain output type. */
} GpioOutputType;


/***************************************************************************************************
 * @brief       GPIO output speed options.
 *
 * @details     This enumeration defines the available output speed options for GPIO pins.
 *              The output speed determines the slew rate of the pins when driving an output signal.
 */
typedef enum {
  kSpeedLow,           /**< Low output speed. */
  kSpeedMedium,        /**< Medium output speed. */
  kSpeedHigh,          /**< High output speed. */
  kSpeedVeryHigh       /**< Very high output speed. */
} GpioOutputSpeed;


/***************************************************************************************************
 * @brief       GPIO pull type options.
 *
 * @details     This enumeration defines the available pull types for GPIO pins.
 *              The pull types determine the internal resistor configuration of the pins.
 */
typedef enum {
  kPullNone,           /**< No pull-up/pull-down. */
  kPullUp,             /**< Pull-up resistor enabled. */
  kPullDown            /**< Pull-down resistor enabled. */
} GpioPullType;


/***************************************************************************************************
 * @brief       Configures the mode of a GPIO pin.
 * 
 * @param       port Pointer to the GPIO port. (Use GPIOx definitios from stm32f410rb.h)
 * @param       pin The pin number to configure. (0 - 15)
 * @param       mode The mode to set for the pin. (from GpioMode enum)
 * 
 * @return      0 if successful, otherwise returns 1 and sets variables errnum and errcode.
 */
int gpioPinSetup(GPIO_Type *port, uint8_t pin, GpioMode mode);


/***************************************************************************************************
 * @brief       Configures the pull type of a GPIO pin.
 *
 * @param       port Pointer to the GPIO port. (Use GPIOx definitios from stm32f410rb.h)
 * @param       pin The pin number to configure. (0 - 15)
 * @param       pull_type The pull type to set for the pin. (from GpioPullType enum)
 * 
 * @return      0 if successful, otherwise returns 1 and sets variables errnum and errcode.
 */
int gpioPinPullTypeSetup(GPIO_Type *port, uint8_t pin, GpioPullType pull_type);


/***************************************************************************************************
 * @brief       Reads the value of a GPIO pin.
 *
 * @param       port Pointer to the GPIO port. (Use GPIOx definitios from stm32f410rb.h)
 * @param       pin The pin number to read from. (0 - 15)
 * @param       read Pointer to store the read value.
 * 
 * @return      0 if successful, otherwise returns 1 and sets variables errnum and errcode.
 */
int gpioPinRead(GPIO_Type *port, uint8_t pin, uint8_t *read);


/***************************************************************************************************
 * @brief       Writes a value to a GPIO pin.
 *
 * @param       port Pointer to the GPIO port. (Use GPIOx definitios from stm32f410rb.h)
 * @param       pin The pin number to write to. (0 - 15)
 * @param       value The value to write. (0 or 1)
 * @param       old_value Pointer to store the previous pin value.
 * 
 * @return      0 if successful, otherwise returns 1 and sets variables errnum and errcode.
 */
int gpioPinWrite(GPIO_Type *port, uint8_t pin, uint8_t value, uint8_t *old_value);


/***************************************************************************************************
 * @brief       Toggles the value of a GPIO pin.
 *
 * @param       port Pointer to the GPIO port. (Use GPIOx definitios from stm32f410rb.h)
 * @param       pin The pin number to toggle. (0 - 15)
 * @param       old_value Pointer to store the previous pin value.
 * 
 * @return      0 if successful, otherwise returns 1 and sets variables errnum and errcode.
 */
int gpioPinToggle(GPIO_Type *port, uint8_t pin, uint8_t *old_value);


/***************************************************************************************************
 * @brief       Sets up an interrupt for a GPIO pin.
 *
 * @param       port Pointer to the GPIO port. (Use GPIOx definitios from stm32f410rb.h)
 * @param       pin The pin number to set up the interrupt for. (0 - 15)
 * @param       rising_edge Set to 1 for rising edge trigger, 0 for falling edge trigger. (0 or 1)
 * @param       priority The interrupt priority level (between 7 and 15).
 * @param       handler Pointer to the interrupt handler function.
 * 
 * @return      0 if successful, otherwise returns 1 and sets variables errnum and errcode.
 */
int gpioInterruptSet(GPIO_Type *port, uint8_t pin, uint8_t rising_edge, uint8_t priority, void (*handler)(void));