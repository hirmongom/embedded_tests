/**
 * @file        main.c
 * 
 * @brief       Driver Test File
 *
 * @details     This file contains a simple program to test the usage of my drivers library.
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
#include <stddef.h>
#include "stm32f410rb.h"
#include "gpio.h"

void buttonHandler(void);

int main(void) {
  gpioPinSetup(GPIOA, 5, kModeOutput);
  gpioPinSetup(GPIOC, 13, kModeInput);
  gpioPinPullTypeSetup(GPIOC, 13, kPullDown);
  gpioInterruptSet(GPIOC, 13, 1, 8, buttonHandler);

  while (1) {}
}

void buttonHandler(void) {
  for (int i = 0; i < 10; i++) {
    gpioPinToggle(GPIOA, 5, NULL);
    for (int j = 0; j < 100000; j++);
    gpioPinToggle(GPIOA, 5, NULL);
    for (int j = 0; j < 100000; j++);
  }
}