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
 * @todo        Manage errors POSIX-style
 *              Function comment blocks
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

#include "gpio.h"
#include "stm32f410rb.h"

static uint8_t initialized_ports[4];


int InitializeGpioPort(GpioPort port) {
  if (port >= 4) return 1;    // Invalid port
  if (initialized_ports[port] == 1) return 1;  // Port already initialized

  switch (port) {
    case kPortA:
      RCC->AHB1ENR |= (1 << 0);
      break;
    case kPortB:
      RCC->AHB1ENR |= (1 << 1);
      break;
    case kPortC:
      RCC->AHB1ENR |= (1 << 2);
      break;
    case kPortH:
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

  initialized_ports[port] = 1;
  return 0;
}


int ConfigureGpioPin(GpioPort port, GpioPinConfig *config) {
  if (initialized_ports[port] == 0) return 1;      // Port is not initialized
  if (config->pins == NULL) return 1;  // Invalid pins array

  GPIO_Type *gpio_port;
  switch (port) {
    case kPortA:
      gpio_port = GPIOA;
      break;
    case kPortB:
      gpio_port = GPIOB;
      break;
    case kPortC:
      gpio_port = GPIOC;
      break;
    case kPortH:
      gpio_port = GPIOH;
      break;
    default:
      return 1;      // Invalid port
      break;
  }

  for (int i = 0; i < config->n_pins; i++) {
    gpio_port->MODER     |=  (config->mode          << (config->pins[i] * 2));      // Set mode
    gpio_port->OTYPER    |=  (config->output_type   <<  config->pins[i]     );      // Set output type
    gpio_port->OSPEEDR   |=  (config->output_speed  << (config->pins[i] * 2));      // Set output speed
    gpio_port->PUPDR     |=  (config->pull_type     << (config->pins[i] * 2));      // Set pull type
  }
  
  return 0;
}


int ToggleOutputGpioPin(GpioPort port, uint8_t pin) {
  // TODO not enough checks
  if (initialized_ports[port] == 0) return 1; // Port not initialized

  switch (port) {
    case kPortA:
      GPIOA->ODR ^= (1 << pin);
      break;
    case kPortB:
      GPIOB->ODR ^= (1 << pin);
      break;
    case kPortC:
      GPIOC->ODR ^= (1 << pin);
      break;
    case kPortH:
      GPIOH->ODR ^= (1 << pin);
      break;
  }

  return 0;
}