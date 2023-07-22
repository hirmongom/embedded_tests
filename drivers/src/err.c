/***************************************************************************************************
 * @file        err.c
 * 
 * @brief       Error Number and Error Code
 * 
 * @details     This file defines a combined error information structure that consists 
 *              of an error number and an error code.
 *              The error number represents the type or category of the error, while the 
 *              error code provides additional specific information about the error.
 * 
 *              The error information is stored in a 32-bit memory location, allowing 
 *              for convenient access and manipulation of the error number and error code 
 *              using a single variable. The structure contains two 16-bit fields:
 *              `errorNumber` and `errorCode`.
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   18/07/2023
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
#include "err.h"

__attribute__((section(".err"))) uint16_t errnum = 0;
__attribute__((section(".err"))) uint16_t errcode = 0;


/***************************************************************************************************
 * @details     This function is used to indicate and handle various error conditions in the system.
 *              It sets the "errnum" and "errcode" variables to specify the type of error and its
 *              code, respectively. After setting the error information, the function enters an
 *              infinite loop to halt the program's execution. During this loop, the built-in LED
 *              connected to pin PA5 (Port A, Pin 5) blinks in a pattern/delay that identifies
 *              the type of error.
 *
 * @note        The error handling loop in this function is intended to stop the program execution
 *              when an error occurs. Developers should ensure that the error conditions are 
 *              properly handled and that the program can recover or exit gracefully based on the 
 *              error type and code set by this function.
 *              
 * @warning     The behavior of the error handling loop and LED blinking pattern/delay may vary 
 *              based on the specific implementation and hardware configuration.
 * 
 * @todo        Implement
 */
void triggerError(uint16_t number, uint16_t code) {
  // Set error vars

  // Initialize GPIOA pin 5

  // Enter loop
}