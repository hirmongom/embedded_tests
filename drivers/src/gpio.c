/**
 * @file        gpio.c
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
 * @date        Last Updated:   09/07/2023
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

extern uint16_t errno;
extern uint16_t errcode;

static void (*gpio_isr_functions[16])(void);

static inline void delay() {
  // TODO make the delay more accurate
  for (volatile uint32_t delay = 0; delay < 100000; ++delay) {}
}

int gpioPinSetup(GPIO_Type *port, uint8_t pin, GpioMode mode) {
  if (pin > 15) {
    errno = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
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
  else {
    errno = 1;  // GPIO error
    errcode = 1;  // Wrong GPIO port
    return 1;
  }

  port->MODER &= ~(3 << pin * 2); // Reset mode before overwritting with new one
  port->MODER |= (mode << pin * 2);

  return 0;
}

// TODO check correct port and if initialized
int gpioPinPullTypeSetup(GPIO_Type *port, uint8_t pin, GpioPullType type) {
  if (pin > 15) {
    errno = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  port->PUPDR &= ~(3 << pin * 2);
  port->PUPDR |= (type << pin * 2);
  return 0;
}

// TODO Check if correct port and if it is initialized and its mode
int gpioPinRead(GPIO_Type *port, uint8_t pin, uint8_t *read) {
  if (pin > 15) {
    errno = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *read = (uint8_t) pin_value;
  return 0;
}

// TODO Check if correct port and if it is initialized and its mode
int gpioPinWrite(GPIO_Type *port, uint8_t pin, uint8_t value, uint8_t *old_value) {
  if (pin > 15) {
    errno = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *old_value = (uint8_t) pin_value;

  if (value == 0) {
    port->ODR &= ~(1 << pin);
  } else if (value == 1) {
    port->ODR |= (1 << pin);
  } else {
    errno = 1;  // GPIO error
    errcode = 5;  // Tried to write wrong value
    return 1;
  }
  
  return 0;
}

// TODO Check if correct port and if it is initialized and its mode
int gpioPinToggle(GPIO_Type *port, uint8_t pin, uint8_t *old_value) {
  if (pin > 15) {
    errno = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *old_value = (uint8_t) pin_value;

  port->ODR ^= (1 << pin);
  return 0;
}

// TODO prio cannot be lower/higher than? I dont understand priorities
/// @see PM0214 page 208
int gpioInterruptSet(GPIO_Type *port, uint8_t pin, uint8_t rising_edge, uint8_t priority, void (*handler)(void)) {
  if (pin > 15) {
    errno = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  if (rising_edge > 1) {
    errno = 1;  // GPIO error
    errcode = 6;  // Wrong value for trigger selection
    return 1;  // Can only be 0 or 1
  }
  if (priority < 7) {
    errno = 1;  // GPIO error
    errcode = 7: // Wrong interrupt priority
    return 1;
  } 
    
  uint8_t exti_source_input;

  if (port == GPIOA)
    exti_source_input = 0;
  else if (port == GPIOB)
    exti_source_input = 1;
  else if (port == GPIOC)
    exti_source_input = 2;
  else if (port == GPIOH)
    exti_source_input = 7;
  else {
    errno = 1;  // GPIO error
    errcode = 1;  // Wrong GPIO port
    return 1;
  }

  RCC->APB2ENR |= (1 << 14);    // Enable system configuration controller clock
  SYSCFG->EXTICR[pin / 4] &= ~(0xF << (pin % 4) * 4); // Clear register
  SYSCFG->EXTICR[pin / 4] |= (exti_source_input << (pin % 4) * 4);  // Select source input for the EXTIx
  
  EXTI->IMR |= (1 << pin);  // Set pin in EXTI line as interrupt
  if (rising_edge == 1) {
    EXTI->RTSR |= (1 << pin); // Enable rising edge trigger
    EXTI->FTSR &= ~(1 << pin);  // Disable falling edge trigger
  } else {
    EXTI->RTSR &= ~(1 << pin);  // Disable rising edge trigger
    EXTI->FTSR |= (1 << pin); // Enable falling edge trigger
  }

  // Set priority and set-enable interrupt
  if (pin <= 4) {
    NVIC->IPR[6 + pin] |= (priority << 4);
    NVIC->ISER[0] |= (1 << (6 + pin));
  } else if (pin <= 9) {
    NVIC->IPR[23] |= (priority << 4);
    NVIC->ISER[0] |= (1 << 23);
  } else {
    NVIC->IPR[40] |= (priority << 4);
    NVIC->ISER[1] |= (1 << 8);
  }

  gpio_isr_functions[pin] = handler;

  return 0;
}

void EXTI0_ISR (void) {
  if (EXTI->PR & (1 << 0)) {
    gpio_isr_functions[0]();
    EXTI->PR |= (1 << 0);    // Clear flag
  }
}

void EXTI1_ISR (void) {
  if (EXTI->PR & (1 << 1)) {
    gpio_isr_functions[1]();
    EXTI->PR |= (1 << 1);    // Clear flag
  }
}

void EXTI2_ISR (void) {
  if (EXTI->PR & (1 << 2)) {
    gpio_isr_functions[2]();
    EXTI->PR |= (1 << 2);    // Clear flag
  }
}

void EXTI3_ISR (void) {
  if (EXTI->PR & (1 << 3)) {
    gpio_isr_functions[3]();
    EXTI->PR |= (1 << 3);    // Clear flag
  }
}

void EXTI4_ISR (void) {
  if (EXTI->PR & (1 << 4)) {
    gpio_isr_functions[4]();
    EXTI->PR |= (1 << 4);    // Clear flag
  }
}

void EXTI9_5_ISR (void) {
  for (int i = 5; i <= 9; i++) {
    if (EXTI->PR & (1 << i)) {
      gpio_isr_functions[i]();
      EXTI->PR |= (1 << i);
    }
  }
}

void EXTI15_10_ISR (void) {
  for (int i = 10; i <= 15; i++) {
    if (EXTI->PR & (1 << i)) {
      gpio_isr_functions[i]();
      EXTI->PR |= (1 << i);
    }
  }
}