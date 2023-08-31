/***************************************************************************************************
 * @file        usart.h
 * 
 * @brief       Header file for the USART2 peripheral
 * 
 * @details     This file provides the necessary definitions and functions for initializing and
 *              using the USART2 peripheral
 * 
 * @author      Hiram Montejano Gómez (hiram.montejano.gomez@gmail.com)
 * 
 * @date        Last Updated: 31/08/2023
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

#ifndef USART2_H
#define USART2_H


#include <stdint.h>
#include <stddef.h>


void usart2_init(void);
void usart2_write_byte(uint8_t byte);
void usart2_write_buffer(char *buffer, size_t length);
uint8_t usart2_read_byte(void);


#endif