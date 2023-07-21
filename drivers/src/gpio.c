/***************************************************************************************************
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


#include <stdint.h>
#include "stm32f410rb.h"
#include "gpio.h"
#include "err.h"


/***************************************************************************************************
 * @brief       Array of function pointers to be executed when an interrupt occurs
 */
static void (*gpio_isr_functions[16])(void);


/***************************************************************************************************
 * @brief       Provides a delay function.
 *
 * @details     This function introduces a delay by executing an empty loop for a fixed number 
 *              of iterations.
 * 
 * @todo        Make use of the RTC to provide a more accurate delay funciton
 * @todo        Make the function usable in a util.c file
 */
static inline void delay() {
  for (volatile uint32_t delay = 0; delay < 100000; ++delay) {}
}


/***************************************************************************************************
 * @details     This function configures the mode of a GPIO pin on the STM32F10RB microcontroller.
 *              The pin number should be within the range 0-15. 
 *              The GPIO port is checked for initialization, and if not initialized, it is enabled. 
 *              The pin mode is then set according to the provided mode.
 *              The mode parameter should be one of the values from the GpioMode enumeration.
 *              Upon successful configuration, the function returns 0. Otherwise, 1 is returned and
 *              variables errnum and errcode are set with the error code.
 * 
 * @todo        Add option to configure port speed
 */
int gpioPinSetup(GPIO_Type *port, uint8_t pin, GpioMode mode) {
  if (pin > 15) {
    errnum = 1;  // GPIO error
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
    errnum = 1;  // GPIO error
    errcode = 1;  // Wrong GPIO port
    return 1;
  }

  port->MODER &= ~(3 << pin * 2); // Reset mode before overwritting with new one
  port->MODER |= (mode << pin * 2);

  return 0;
}


/***************************************************************************************************
 * @details     This function configures the pull type of a GPIO pin on the STM32F10RB 
 *              microcontroller.
 *              The function checks if the provided GPIO port is correct and initialized.
 *              The pin number should be within the range 0-15. 
 *              The pull type is then set according to the provided type, which should be one of 
 *              the values from the GpioPullType enumeration.
 *              Upon successful configuration, the function returns 0. Otherwise, 1 is returned and
 *              variables errnum and errcode are set with the error code.
 *
 * @todo        Check if port is correct and if it is initializated
 */
int gpioPinPullTypeSetup(GPIO_Type *port, uint8_t pin, GpioPullType pull_type) {
  if (pin > 15) {
    errnum = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  port->PUPDR &= ~(3 << pin * 2);
  port->PUPDR |= (pull_type << pin * 2);
  return 0;
}


/***************************************************************************************************
 * @details     This function reads the value of a GPIO pin on the STM32F10RB microcontroller.
 *              The pin number should be within the range 0-15.
 *              The function checks if the provided GPIO port is correct and initialized,
 *              as well as the mode of the pin.
 *              Upon successful read, the function stores the read value in the memory location
 *              pointed to by the 'read' parameter.
 *              The read value will be either 0 or 1, indicating the logic level of the pin.
 *              If an error occurs, 1 is returned, and variables errnum and errcode are set with
 *              the error code.
 *
 * @todo        Check if the GPIO port is correct and if it is initialized and in the appropriate 
 *              mode.
 */
int gpioPinRead(GPIO_Type *port, uint8_t pin, uint8_t *read) {
  if (pin > 15) {
    errnum = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *read = (uint8_t) pin_value;
  return 0;
}


/***************************************************************************************************
 * @details     This function writes a value (0 or 1) to a GPIO pin on the STM32F10RB 
 *              microcontroller.
 *              The pin number should be within the range 0-15.
 *              The function checks if the provided GPIO port is correct and initialized,
 *              as well as the mode of the pin.
 *              The previous value of the pin is stored in the memory location pointed to by the 
 *              'old_value' parameter.
 *              If the 'value' parameter is 0, the pin is cleared (set to logic low).
 *              If the 'value' parameter is 1, the pin is set (set to logic high).
 *              If an error occurs, 1 is returned, and variables errnum and errcode are set with
 *              the error code.
 *
 * @todo        Check if the GPIO port is correct and if it is initialized and in the appropriate 
 *              mode.
 */
int gpioPinWrite(GPIO_Type *port, uint8_t pin, uint8_t value, uint8_t *old_value) {
  if (pin > 15) {
    errnum = 1;  // GPIO error
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
    errnum = 1;  // GPIO error
    errcode = 5;  // Tried to write wrong value
    return 1;
  }
  
  return 0;
}


/***************************************************************************************************
 * @details     This function toggles the value of a GPIO pin on the STM32F10RB microcontroller.
 *              The pin number should be within the range 0-15.
 *              The function checks if the provided GPIO port is correct and initialized,
 *              as well as the mode of the pin.
 *              The previous value of the pin is stored in the memory location pointed to by the 
 *              'old_value' parameter.
 *              If the pin is currently low, it is toggled to high. If the pin is currently high,
 *              it is toggled to low.
 *              If an error occurs, 1 is returned, and variables errnum and errcode are set with
 *              the error code.
 *
 * @todo        Check if the GPIO port is correct and if it is initialized and in the appropriate mode.
 */
int gpioPinToggle(GPIO_Type *port, uint8_t pin, uint8_t *old_value) {
  if (pin > 15) {
    errnum = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  
  uint32_t pin_value = (port->IDR >> pin) & 0x01;
  *old_value = (uint8_t) pin_value;

  port->ODR ^= (1 << pin);
  return 0;
}


/***************************************************************************************************
 * @details     This function sets up an interrupt for a GPIO pin on the STM32F10RB microcontroller.
 *              The pin number should be within the range 0-15.
 *              The function checks if the provided GPIO port is correct and initialized.
 *              It also validates the rising_edge and priority parameters.
 *              The interrupt trigger type is set based on the rising_edge parameter,
 *              with 1 indicating a rising edge trigger and 0 indicating a falling edge trigger.
 *              The priority parameter sets the interrupt priority level, which should be between
 *              7 and 15 (inclusive).
 *              The handler parameter is a pointer to the interrupt handler function that will be 
 *              executed when the interrupt occurs.
 *              Upon successful setup, the function returns 0.
 *              If an error occurs, 1 is returned, and variables errnum and errcode are set with
 *              the appropriate error codes.
 *
 * @todo        Check if the GPIO port is correct and if it is initialized.
 * @todo        Clarify the allowed range for the priority parameter and which value is higher prio
 */
int gpioInterruptSet(GPIO_Type *port, uint8_t pin, uint8_t rising_edge, uint8_t priority, void (*handler)(void)) {
  if (pin > 15) {
    errnum = 1;  // GPIO error
    errcode = 2;  // Wrong pin number
    return 1;
  }
  if (rising_edge > 1) {
    errnum = 1;  // GPIO error
    errcode = 6;  // Wrong value for trigger selection
    return 1;  // Can only be 0 or 1
  }
  if (priority < 7) {
    errnum = 1;  // GPIO error
    errcode = 7; // Wrong interrupt priority
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
    errnum = 1;  // GPIO error
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


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI0.
 *
 * @details     This ISR is triggered when an interrupt occurs on EXTI line 0.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[0].
 *              After handling the interrupt, it clears the interrupt flag for EXTI line 0.
 */
static void EXTI0_ISR (void) {
  if (EXTI->PR & (1 << 0)) {
    gpio_isr_functions[0]();
    EXTI->PR |= (1 << 0);    // Clear flag
  }
}


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI1.
 *
 * @details     This ISR is triggered when an interrupt occurs on EXTI line 1.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[1].
 *              After handling the interrupt, it clears the interrupt flag for EXTI line 1.
 */
static void EXTI1_ISR (void) {
  if (EXTI->PR & (1 << 1)) {
    gpio_isr_functions[1]();
    EXTI->PR |= (1 << 1);    // Clear flag
  }
}


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI2.
 *
 * @details     This ISR is triggered when an interrupt occurs on EXTI line 2.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[2].
 *              After handling the interrupt, it clears the interrupt flag for EXTI line 2.
 */
static void EXTI2_ISR (void) {
  if (EXTI->PR & (1 << 2)) {
    gpio_isr_functions[2]();
    EXTI->PR |= (1 << 2);    // Clear flag
  }
}


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI3.
 *
 * @details     This ISR is triggered when an interrupt occurs on EXTI line 3.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[3].
 *              After handling the interrupt, it clears the interrupt flag for EXTI line 3.
 */
static void EXTI3_ISR (void) {
  if (EXTI->PR & (1 << 3)) {
    gpio_isr_functions[3]();
    EXTI->PR |= (1 << 3);    // Clear flag
  }
}


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI4.
 *
 * @details     This ISR is triggered when an interrupt occurs on EXTI line 4.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[4].
 *              After handling the interrupt, it clears the interrupt flag for EXTI line 4.
 */
static void EXTI4_ISR (void) {
  if (EXTI->PR & (1 << 4)) {
    gpio_isr_functions[4]();
    EXTI->PR |= (1 << 4);    // Clear flag
  }
}


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI lines 5 to 9.
 *
 * @details     This ISR is triggered when an interrupt occurs on any of the EXTI lines 5 to 9.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[i] for each triggered EXTI line.
 *              After handling the interrupts, it clears the corresponding interrupt flags for 
 *              EXTI lines 5 to 9.
 */
static void EXTI9_5_ISR (void) {
  for (int i = 5; i <= 9; i++) {
    if (EXTI->PR & (1 << i)) {
      gpio_isr_functions[i]();
      EXTI->PR |= (1 << i);
    }
  }
}


/***************************************************************************************************
 * @brief       Interrupt Service Routine for EXTI lines 10 to 15.
 *
 * @details     This ISR is triggered when an interrupt occurs on any of the EXTI lines 10 to 15.
 *              It calls the associated GPIO interrupt handler function stored in 
 *              gpio_isr_functions[i] for each triggered EXTI line.
 *              After handling the interrupts, it clears the corresponding interrupt flags for 
 *              EXTI lines 10 to 15.
 */
static void EXTI15_10_ISR (void) {
  for (int i = 10; i <= 15; i++) {
    if (EXTI->PR & (1 << i)) {
      gpio_isr_functions[i]();
      EXTI->PR |= (1 << i);
    }
  }
}