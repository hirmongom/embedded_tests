/**
 * @file        startup.c
 * 
 * @brief       Startup file for the STM32F410 line of microcontrollers
 * 
 * @details     This code defines the Nested Vectored Interrupt Controller (NVIC)
 *              with the corresponding interrupts defined in the reference manual RM0401.
 *              It implements the Reset_ISR(), which copies the .data section from
 *              flash memory to SRAM and initializes it to zero. It also initializes the
 *              .bss section in SRAM to zero. Finally, it calls the main() function as
 *              the program's entry point
 * 
 * @author      Hiram Montejano Gómez
 * 
 * @date        Last Updated:   17/06/2023
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

#define     SRAM_START      0x20000000U
#define     SRAM_SIZE       (32 * 1024)
#define     SRAM_END        (SRAM_START + SRAM_SIZE)
#define     STACK_START     SRAM_END

#define OVERRIDABLE_ISR     __attribute__((weak, alias("Default_ISR")))

void Default_ISR(void);
void Reset_ISR(void);

void NMI_ISR(void)                      OVERRIDABLE_ISR;
void HardFault_ISR(void)                OVERRIDABLE_ISR;
void MemManage_ISR(void)                OVERRIDABLE_ISR;
void BusFault_ISR(void)                 OVERRIDABLE_ISR;
void UsageFault_ISR(void)               OVERRIDABLE_ISR;
void SVCall_ISR(void)                   OVERRIDABLE_ISR;
void DebugMonitor_ISR(void)             OVERRIDABLE_ISR;
void PendSV_ISR(void)                   OVERRIDABLE_ISR;
void Systick_ISR(void)                  OVERRIDABLE_ISR;
void WWDG_ISR(void)                     OVERRIDABLE_ISR;
void PVD_ISR(void)                      OVERRIDABLE_ISR;
void EXTI21_TAMP_STAMP_ISR(void)        OVERRIDABLE_ISR;
void EXTI22_RTC_WKUP_ISR(void)          OVERRIDABLE_ISR;
void TAMPER_STAMP_ISR(void)             OVERRIDABLE_ISR;
void RTC_WKUP_ISR(void)                 OVERRIDABLE_ISR;
void FLASH_ISR(void)                    OVERRIDABLE_ISR;
void RCC_ISR(void)                      OVERRIDABLE_ISR;
void EXTI0_ISR(void)                    OVERRIDABLE_ISR;
void EXTI1_ISR(void)                    OVERRIDABLE_ISR;
void EXTI2_ISR(void)                    OVERRIDABLE_ISR;
void EXTI3_ISR(void)                    OVERRIDABLE_ISR;
void EXTI4_ISR(void)                    OVERRIDABLE_ISR;
void DMA1_Stream0_ISR(void)             OVERRIDABLE_ISR;
void DMA1_Stream1_ISR(void)             OVERRIDABLE_ISR;
void DMA1_Stream2_ISR(void)             OVERRIDABLE_ISR;
void DMA1_Stream3_ISR(void)             OVERRIDABLE_ISR;
void DMA1_Stream4_ISR(void)             OVERRIDABLE_ISR;
void DMA1_Stream5_ISR(void)             OVERRIDABLE_ISR;
void DMA1_Stream6_ISR(void)             OVERRIDABLE_ISR;
void ADC_ISR(void)                      OVERRIDABLE_ISR;
void EXTI9_5_ISR(void)                  OVERRIDABLE_ISR;
void TIM1_BRK_TIM9_ISR(void)            OVERRIDABLE_ISR;
void TIM1_UP_ISR(void)                  OVERRIDABLE_ISR;
void TIM1_TRG_COM_TIM11_ISR(void)       OVERRIDABLE_ISR;
void TIM1_CC_ISR(void)                  OVERRIDABLE_ISR;
void I2C1_EV_ISR(void)                  OVERRIDABLE_ISR;
void I2C1_ER_ISR(void)                  OVERRIDABLE_ISR;
void I2C2_EV_ISR(void)                  OVERRIDABLE_ISR;
void I2C2_ER_ISR(void)                  OVERRIDABLE_ISR;
void SPI1_ISR(void)                     OVERRIDABLE_ISR;
void SPI2_ISR(void)                     OVERRIDABLE_ISR;
void USART1_ISR(void)                   OVERRIDABLE_ISR;
void USART2_ISR(void)                   OVERRIDABLE_ISR;
void EXTI15_10_ISR(void)                OVERRIDABLE_ISR;
void EXTI17_RTC_Alarm_ISR(void)         OVERRIDABLE_ISR;
void RTC_Alarm_ISR(void)                OVERRIDABLE_ISR;
void DMA1_Stream7_ISR(void)             OVERRIDABLE_ISR;
void TIM5_ISR(void)                     OVERRIDABLE_ISR;
void TIM6_DAC_ISR(void)                 OVERRIDABLE_ISR;
void DMA2_Stream0_ISR(void)             OVERRIDABLE_ISR;
void DMA2_Stream1_ISR(void)             OVERRIDABLE_ISR;
void DMA2_Stream2_ISR(void)             OVERRIDABLE_ISR;
void DMA2_Stream3_ISR(void)             OVERRIDABLE_ISR;
void DMA2_Stream4_ISR(void)             OVERRIDABLE_ISR;
void EXTI19_ISR(void)                   OVERRIDABLE_ISR;
void DMA2_Stream5_ISR(void)             OVERRIDABLE_ISR;
void DMA2_Stream6_ISR(void)             OVERRIDABLE_ISR;
void DMA2_Stream7_ISR(void)             OVERRIDABLE_ISR;
void USART6_ISR(void)                   OVERRIDABLE_ISR;
void EXTI20_ISR(void)                   OVERRIDABLE_ISR;
void RNG_ISR(void)                      OVERRIDABLE_ISR;
void FPU_ISR(void)                      OVERRIDABLE_ISR;
void SPI5_ISR(void)                     OVERRIDABLE_ISR;
void I2C4_EV_ISR(void)                  OVERRIDABLE_ISR;
void I2C4_ER_ISR(void)                  OVERRIDABLE_ISR;
void EXTI23_LPTIM1_ISR(void)            OVERRIDABLE_ISR;


/**
 * @brief Vector Table for Nested Vectored Interrupt Controller (NVIC)
 *
 * This array represents the vector table used by the Nested Vectored Interrupt Controller (NVIC)
 * to handle various interrupts and exceptions in the system. Each entry in the table corresponds
 * to a specific interrupt or exception and points to the corresponding interrupt service routine (ISR).
 *
 * @note The vector table is defined as an array of 32-bit unsigned integers (uint32_t).
 *
 * @warning Modifying the vector table requires a deep understanding of the system's interrupt handling
 * mechanisms and should only be done with caution and in accordance with the RM0401 reference manual.
 *
 * @see RM0401 Reference Manual, Page 198 for more information on the NVIC and the vector table.
 */
uint32_t NVIC[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)&Reset_ISR,
    (uint32_t)&NMI_ISR,
    (uint32_t)&HardFault_ISR,
    (uint32_t)&MemManage_ISR,
    (uint32_t)&BusFault_ISR,
    (uint32_t)&UsageFault_ISR,
    0,
    0,
    0,
    0,
    (uint32_t)&SVCall_ISR,
    (uint32_t)&DebugMonitor_ISR,
    0,
    (uint32_t)&PendSV_ISR,
    (uint32_t)&Systick_ISR,
    (uint32_t)&WWDG_ISR,
    (uint32_t)&PVD_ISR,
    (uint32_t)&EXTI21_TAMP_STAMP_ISR,
    (uint32_t)&EXTI22_RTC_WKUP_ISR,
    (uint32_t)&FLASH_ISR,
    (uint32_t)&RCC_ISR,
    (uint32_t)&EXTI0_ISR,
    (uint32_t)&EXTI1_ISR,
    (uint32_t)&EXTI2_ISR,
    (uint32_t)&EXTI3_ISR,
    (uint32_t)&EXTI4_ISR,
    (uint32_t)&DMA1_Stream0_ISR,
    (uint32_t)&DMA1_Stream1_ISR,
    (uint32_t)&DMA1_Stream2_ISR,
    (uint32_t)&DMA1_Stream3_ISR,
    (uint32_t)&DMA1_Stream4_ISR,
    (uint32_t)&DMA1_Stream5_ISR,
    (uint32_t)&DMA1_Stream6_ISR,
    (uint32_t)&ADC_ISR,
    0,
    0,
    0,
    0,
    (uint32_t)&EXTI9_5_ISR,
    (uint32_t)&TIM1_BRK_TIM9_ISR,
    (uint32_t)&TIM1_UP_ISR,
    (uint32_t)&TIM1_TRG_COM_TIM11_ISR,
    (uint32_t)&TIM1_CC_ISR,
    0,
    0,
    0,
    (uint32_t)&I2C1_EV_ISR,
    (uint32_t)&I2C1_ER_ISR,
    (uint32_t)&I2C2_EV_ISR,
    (uint32_t)&I2C2_ER_ISR,
    (uint32_t)&SPI1_ISR,
    (uint32_t)&SPI2_ISR,
    (uint32_t)&USART1_ISR,
    (uint32_t)&USART2_ISR,
    0,
    (uint32_t)&EXTI15_10_ISR,
    (uint32_t)&EXTI17_RTC_Alarm_ISR,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&DMA1_Stream7_ISR,
    0,
    0,
    (uint32_t)&TIM5_ISR,
    0,
    0,
    0,
    (uint32_t)&TIM6_DAC_ISR,
    0,
    (uint32_t)&DMA2_Stream0_ISR,
    (uint32_t)&DMA2_Stream1_ISR,
    (uint32_t)&DMA2_Stream2_ISR,
    (uint32_t)&DMA2_Stream3_ISR,
    (uint32_t)&DMA2_Stream4_ISR,
    0,
    (uint32_t)&EXTI19_ISR,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&DMA2_Stream5_ISR,
    (uint32_t)&DMA2_Stream6_ISR,
    (uint32_t)&DMA2_Stream7_ISR,
    (uint32_t)&USART6_ISR,
    0,
    0,
    0,
    0,
    (uint32_t)&EXTI20_ISR,
    0,
    0,
    0,
    (uint32_t)&RNG_ISR,
    (uint32_t)&FPU_ISR,
    0,
    0,
    0,
    (uint32_t)&SPI5_ISR,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&I2C4_EV_ISR,
    (uint32_t)&I2C4_ER_ISR,
    (uint32_t)&EXTI23_LPTIM1_ISR
};

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/**
 * @brief Main function
 *
 * This is the entry point of the program. It is called after the reset sequence and
 * performs necessary initialization before calling the user-defined main function.
 *
 * @return Integer value representing the exit status of the program.
 */
int main(void);

/**
 * @brief Reset Interrupt Service Routine (ISR)
 *
 * This ISR is invoked when a reset occurs. It is responsible for initializing
 * the .data section by copying the data from FLASH to SRAM, initializing the .bss section
 * by setting it to zero, and then calling the user-defined main function.
 */
void Reset_ISR(void) {
    // Copy .data section to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDestination = (uint8_t*)&_sdata;  // SRAM
    uint8_t *pSource = (uint8_t*)&_etext;   // FLASH

    asm volatile(
        "mov r0, %[pDestination]\n"     // Load the start address of the destination into r0
        "mov r1, %[size]\n"             // Load the size of the copy into r1
        "mov r2, #0\n"                  // Initialize r2 with zero

        "copy_loop:\n"
            "cmp r1, #0\n"              // Compare the size with zero
            "beq copy_end\n"            // Branch to copy_end if size is zero
            "ldrb r3, [%[pSource]]\n"   // Load a byte from the source address
            "strb r3, [r0], #1\n"       // Store the byte to the destination address and increment the destination pointer
            "subs r1, r1, #1\n"         // Subtract 1 from size
            "b copy_loop\n"             // Branch back to copy_loop

        "copy_end:\n"
        :
        : [pDestination] "r" (pDestination), [size] "r" (size), [pSource] "r" (pSource)
        : "r0", "r1", "r2", "r3"
    );

    // Initialize .bss section to zero
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDestination = (uint8_t*)&_sbss;
        
    asm volatile(
        "mov r0, %[dest]\n"             // Load the start address of .bss section into r0
        "mov r1, %[size]\n"             // Load the size of .bss section into r1
        "mov r2, #0\n"                  // Initialize r2 with zero

        "loop:\n"
            "cmp r1, #0\n"              // Compare the size with zero
            "beq end\n"                 // Branch to end if size is zero
            "strb r2, [r0], #1\n"       // Store byte zero at the current address and increment the address
            "subs r1, r1, #1\n"         // Subtract 1 from size
            "b loop\n"                  // Branch back to the loop

        "end:\n"
        :
        : [dest] "r" (pDestination), [size] "r" (size)
        : "r0", "r1", "r2"
    );

    // Call program entry point
    main();
}

/**
 * @brief Default Interrupt Service Routine (ISR)
 *
 * This ISR is a placeholder for all other interrupts that do not have a dedicated ISR defined.
 * It enters an infinite loop, effectively halting the system when an unexpected interrupt occurs.
 */
void Default_ISR(void) {
    while(1);
}