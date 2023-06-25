/**
 * @file        main.c
 * 
 * @brief       LED Blinking Application
 *
 * @details     This file contains a simple program to blink an LED connected 
 *              to Pin PA5 of the STM32F10RB microcontroller.
 *              The led blinks rapidly while the user button is not pressed.
 *              If the user button is pressed, the blinking speed lowers until the
 *              button is released
 * 
 * @note        This program utilizes the Nucleo board's built-in user LED and user button, 
 *              which are connected to PA5 and PC13, respectively.
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

#include "gpio.h"

int main(void) {
  GpioPinConfig pin_config = GPIO_PIN_CONFIG_DEFAULT;
  pin_config.pins = (uint8_t[]){5};
  pin_config.n_pins = 1;
  pin_config.mode = kModeOutput;
  pin_config.output_type = kOtypePushPull;
  pin_config.output_speed = kSpeedLow;
  pin_config.pull_type = kPullNone;

  InitializeGpioPort(kPortA);
  ConfigureGpioPin(kPortA, &pin_config);

  while (1) {
      ToggleOutputGpioPin(kPortA, 5);
      for (uint32_t i = 0; i < 100000; i++);
  }
  return 0;
}