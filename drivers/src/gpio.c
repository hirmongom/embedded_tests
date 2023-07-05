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

#include <stdint.h>
#include "stm32f410rb.h"
#include "gpio.h"


extern void (*EXTI0_ISR)(void);
extern void (*EXTI1_ISR)(void);
extern void (*EXTI2_ISR)(void);
extern void (*EXTI3_ISR)(void);
extern void (*EXTI4_ISR)(void);
extern void (*EXTI9_5_ISR)(void);
extern void (*EXTI15_10_ISR)(void);


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

// TODO prio cannot be lower than?
/// @see PM0214 page 208
int gpioInterruptSet(GPIO_Type *port, uint8_t pin, uint8_t rising_edge, uint8_t priority, void (*handler)(void)) {
  if (pin > 15) return 1; // Wrong pin
  if (rising_edge > 1) return 1;  // Can only be 0 or 1
  if (priority < 7) return 1; // Cannot have more priority

  uint8_t exti_source_input;
  uint8_t exti_line = pin / 4;

  if (port == GPIOA)
    exti_source_input = 0;
  else if (port == GPIOB)
    exti_source_input = 1;
  else if (port == GPIOC)
    exti_source_input = 2;
  else if (port == GPIOH)
    exti_source_input = 7;
  else   
    return 1; // Wrong port

  RCC->APB2ENR |= (1 << 14);    // Enable system configuration controller clock
  SYSCFG->EXTICR[exti_line] &= ~(0xF << (pin % 4) * 4); // Clear register
  SYSCFG->EXTICR[exti_line] |= (exti_source_input << (pin % 4) * 4);  // Select source input for the EXTIx
  
  EXTI->IMR |= (1 << pin);  // Set pin in EXTI line as interrupt
  if (rising_edge == 1) {
    EXTI->RTSR |= (1 << pin); // Enable rising edge trigger
    EXTI->FTSR &= ~(1 << pin);  // Disable falling edge trigger
  } else {
    EXTI->RTSR &= ~(1 << pin);  // Disable rising edge trigger
    EXTI->FTSR |= (1 << pin); // Enable falling edge trigger
  }

  // Set priority and set-enable interrupt
  if (exti_line <= 4) {
    NVIC->IPR[(6 + exti_line) / 4] |= (priority << (((6 + exti_line) % 4) * 8));
    NVIC->ISER[0] |= (1 << (6 + pin));
  } else if (exti_line <= 9) {
    NVIC->IPR[5] |= (priority << 24);
    NVIC->ISER[0] |= (1 << 23);
  } else {
    NVIC->IPR[10] |= (priority << 0);
    NVIC->ISER[1] |= (1 << 8);
  }

  switch (exti_line) {
    case 0:
      EXTI0_ISR = handler;
      break;
    case 1:
      EXTI1_ISR = handler;
      break;
    case 2:
      EXTI2_ISR = handler;
      break;
    case 3:
      EXTI3_ISR = handler;
      break;
    case 4:
      EXTI4_ISR = handler;
      break;
    default:
      if (exti_line <= 9) {
        EXTI9_5_ISR = handler;
      } else {
        EXTI15_10_ISR = handler;
      }
      break;
  }

  return 0;
}