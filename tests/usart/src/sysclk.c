/***************************************************************************************************
 * @file        sysclk.c
 * 
 * @brief       Source file for System Clock
 * 
 * @details     This file implements the functions for configuring the System Clock.
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


#include "stm32f410rb.h"


/**************************************************************************************************/
static inline void confiugre_pll(void) {
/* 
 * Configuring the PLL (Phase-Locked Loop) for the desired system clock:
 * 
 * 1. PLL_M: This value is directly set to the lowest bits [5:0] of the PLLCFGR register.
 *           It divides the input clock before it's fed to the VCO (Voltage-Controlled Oscillator).
 * 
 * 2. PLL_N: This value is shifted to the left by 6 bits and set to bits [14:6] of the PLLCFGR 
 *           register.
 *           It determines the multiplication factor for the VCO (Voltage-Controlled Oscillator).
 * 
 * 3. PLL_P: This value determines the division factor for the main system clock.
 *           The formula `((PLL_P >> 1) - 1)` is used to convert the actual division factor 
 *           (2, 4, 6, or 8) to the respective 2-bit representation in the PLLCFGR register.
 *           This value is then shifted to the left by 16 bits and set to bits [17:16].
 * 
 * 4. PLL_Q: This value is shifted to the left by 24 bits and set to bits [27:24] of the PLLCFGR 
 *           register.
 *           It determines the division factor for the USB OTG FS, SDIO, and RNG clocks.
 * 
 * 5. (1 << 22): This bit sets the PLL source to HSE (High-Speed External) clock. If this bit is 
 *               reset, then HSI (High-Speed Internal) is used as the PLL source.
 */
  RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (PLL_Q << 24) | (1 << 22);
}


/**************************************************************************************************/
static inline void configure_flash(void) {
/* Configure the Flash Access Control Register (ACR)
 * - (1 << 8): Prefetch enable. When set, it allows the Flash to fetch instructions before they are needed.
 * - (1 << 9): Instruction cache enable. When set, it caches recently used instructions to speed up execution.
 * - (1 << 10): Data cache enable. When set, it caches recently accessed data for faster access.
 * - (5 << 0): Sets the Flash latency to 5 wait states. This is the number of CPU cycles that the memory access instruction will stall until the data is fetched from Flash.
 */
  FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10 ) | (5 << 0);
}


/**************************************************************************************************/
void set_system_clock(void) {
  RCC->CR |= (1 << 16);   // Enable HSE clock
  while(!(RCC->CR & (1 << 17)));    // Wait for HSE clock ready flag

  RCC->APB1ENR |= (1 << 28);  // Enable Power Interface clock
  PWR->CR |= (1 << 14);   // Scale 3 mode <= 64MHz 

  RCC->CFGR |= (0 << 7);    // (0b0xxx) AHB prescaler = system clock not divided  
  RCC->CFGR |= (5 << 10);   // (0b101) APB low speed prescaler = AHB / 4
  RCC->CFGR |= (4 << 13);   // (0b100) APB high speed prescaler = AHB / 2

  configure_pll();

  RCC->CR |= (1 << 24);   // Enable main PLL
  while (!(RCC->CR & (1 << 25)));   // Wait for PLL clock ready flag

  configure_flash();

	RCC->CFGR |= (2 << 0);    // Set PLL as system clock
  while(!(RCC->CFGR & (2 << 2)));   // Wait until PLL system clock status flag
}