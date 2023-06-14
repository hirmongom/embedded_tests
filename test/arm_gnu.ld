/**
 * @file        arm_gnu.ld
 * 
 * @brief       Linker script for the STM32F10 line of microcontrollers
 * 
 * @details     This linker script is designed for the STM32F10 line of microcontrollers,
 *              specifically the STM32F410RB microcontroller. It provides memory layout
 *              and section placement information for the firmware image.
 * 
 *              The script defines the memory regions for the FLASH (program memory) and SRAM
 *              (data memory) and specifies the placement of various sections such as .text,
 *              .rodata, .data, and .bss.
 * 
 *              The .text section contains the interrupt vector table, code, and read-only data.
 *              It is placed in the FLASH memory.
 * 
 *              The .data section contains initialized global and static variables that are copied
 *              from the FLASH to the SRAM during startup. It is placed in the SRAM but loaded from
 *              the FLASH memory.
 * 
 *              The .bss section contains uninitialized global and static variables that are
 *              zero-initialized during startup. It is placed in the SRAM.
 * 
 *              The .heap and .stack sections, which are responsible for dynamic memory allocation
 *              and the program stack, are left unspecified in the linker script. This allows for
 *              flexibility in memory allocation at runtime, avoiding potential limitations
 *              imposed by fixed sizes. However, it should be noted that this approach may incur
 *              some efficiency overhead.
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        14/06/2023
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


ENTRY(Reset_Handler)

MEMORY {
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS {
    .text : {
        *(.isr_vector)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    .data : {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT> FLASH

    .bss : {
        _sbss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM
}
