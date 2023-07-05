/**
 * @file        main.c
 * 
 * @brief       Driver Test File
 *
 * @details     This file contains a simple program to test the usage of my drivers library.
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
#include <stddef.h>
#include "stm32f410rb.h"
#include "gpio.h"

void buttonHandler(void);

uint8_t pSpeed = 0;

int main(void) {
  gpioPinSetup(GPIOA, 5, kModeOutput);
  gpioPinSetup(GPIOC, 13, kModeInput);
  gpioInterruptSet(GPIOC, 13, 1, 8, &buttonHandler);

  uint32_t speed[] = {100000, 250000, 500000, 750000, 1000000};

  while (1) {
    gpioPinToggle(GPIOA, 5, NULL);
    for (uint32_t i = 0; i < speed[pSpeed]; i++);
  }

  return 0;
}

void buttonHandler(void) {
  pSpeed ++;
  pSpeed = pSpeed % 5;
}