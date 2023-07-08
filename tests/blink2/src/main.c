/**
 * @file        main.c
 * 
 * @brief       Driver Test File
 *
 * @details     This file contains a simple program to test the usage of my drivers library.
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   08/07/2023
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

void buttonHandler1(void);
void buttonHandler2(void);
void buttonHandler3(void);
void buttonHandler4(void);

int main(void) {
  gpioPinSetup(GPIOA, 5, kModeOutput);
  gpioPinSetup(GPIOC, 13, kModeInput);
  gpioPinSetup(GPIOC, 4, kModeInput);
  gpioPinSetup(GPIOC, 7, kModeInput);
  gpioPinSetup(GPIOA, 12, kModeInput);
  gpioPinPullTypeSetup(GPIOC, 13, kPullDown);
  gpioPinPullTypeSetup(GPIOC, 4, kPullDown);
  gpioPinPullTypeSetup(GPIOC, 7, kPullDown);
  gpioPinPullTypeSetup(GPIOA, 12, kPullDown);
  gpioInterruptSet(GPIOC, 13, 1, 12, buttonHandler1);
  gpioInterruptSet(GPIOC, 4, 1, 9, buttonHandler2);
  gpioInterruptSet(GPIOC, 7, 1, 10, buttonHandler3);
  gpioInterruptSet(GPIOA, 12, 1, 8, buttonHandler4);

  while (1) {}
}

void buttonHandler1(void) {
  for (int i = 0; i < 20; i++) {
    gpioPinToggle(GPIOA, 5, NULL);
    for (int j = 0; j < 100000; j++);
  }
}

void buttonHandler2(void) {
  gpioPinToggle(GPIOA, 5, NULL);
}

void buttonHandler3(void) {
  gpioPinToggle(GPIOA, 5, NULL);
  for (int i = 0; i < 10000000; i++);
  gpioPinToggle(GPIOA, 5, NULL);
}

void buttonHandler4(void) {
  gpioPinWrite(GPIOA, 5, 0, NULL);
}