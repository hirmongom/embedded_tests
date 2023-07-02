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

#include <stdint.h>
#include "stm32f410rb.h"
#include "gpio.h"

static inline void delay() {
  // TODO make the delay more accurate
  for (volatile uint32_t delay = 0; delay < 100000; ++delay) {}
} 

int gpioPinSetup(GPIO_Type *port, uint8_t pin, GpioMode mode) {
  if (pin > 15) return 1; // Wrong pin
  
  // Check if port is initializated, if not, initialize it
  if (port == GPIOA) {
    if (!(RCC->AHB1ENR & (1 << 0))) {
      RCC->AHB1ENR |= (1 << 0);
      delay();
    }
  } else if (port == GPIOB) {
    if (!(RCC->AHB1ENR & (1 << 1))) {
      RCC->AHB1ENR |= (1 << 1);
      delay();
    } 
  }
  else if (port == GPIOC) {
    if (!(RCC->AHB1ENR & (1 << 2))) {
      RCC->AHB1ENR |= (1 << 2);
      delay();
    }
  }
  else if (port == GPIOH) {
    if (!(RCC->AHB1ENR & (1 << 7))) {
      RCC->AHB1ENR |= (1 << 7);
      delay();
    }
  }
  else   
    return 1; // Wrong port

  port->MODER &= ~(3 << pin * 2); // Reset mode before overwritting with new one
  port->MODER |= (mode << pin * 2);

  return 0;
}

int gpioPinPullTypeSetup(GPIO_Type *port, uint8_t pin, GpioPullType type) {
  if (pin > 15) return 1; // Wrong pin
  
  port->PUPDR &= ~(3 << pin * 2);
  port->PUPDR |= (type << pin * 2);
  return 0;
}


// TODO should check if correct port or if it is initialized and its mode
int gpioPinRead(GPIO_Type *port, uint8_t pin, uint8_t *read) {
  if (pin > 15) return 1; // Wrong pin
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *read = (uint8_t) pin_value;
  return 0;
}


int gpioPinWrite(GPIO_Type *port, uint8_t pin, uint8_t value, uint8_t *old_value) {
  if (pin > 15) return 1; // Wrong pin
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *old_value = (uint8_t) pin_value;

  port->ODR |= (value << pin);
  return 0;
}


int gpioPinToggle(GPIO_Type *port, uint8_t pin, uint8_t *old_value) {
  if (pin > 15) return 1; // Wrong pin
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *old_value = (uint8_t) pin_value;

  port->ODR ^= (1 << pin);
  return 0;
}