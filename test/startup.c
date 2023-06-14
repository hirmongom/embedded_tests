/**
 * @file		startup.c
 * 
 * @brief 		Startup file for the STM32F410 line of microcontrollers
 * 
 * @author 		Hiram Montejano Gómez
 * 
 * @date 		14/06/2023
 * 
 * @copyright 	This file is part of the "STM32F10RB Microcontroller Applications" project.
 * 
 * 				Every file is free software: you can redistribute it and/or modify
 * 				it under the terms of the GNU General Public License as published by
 * 				the Free Software Foundation, either version 3 of the License, or
 * 				(at your option) any later version.
 * 
 * 				These files are distributed in the hope that they will be useful,
 * 				but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * 				GNU General Public License for more details.
 * 
 * 				You should have received a copy of the GNU General Public License
 * 				along with the "STM32F10RB Microcontroller Applications" project. If not, 
 * 				see <http://www.gnu.org/licenses/>.
 */

#define		SRAM_START		0x20000000U
#define		SRAM_SIZE		(32 * 1024)
#define		SRAM_END		(SRAM_START + SRAM_SIZE)
#define		STACK_START		SRAM_END

#define OVERRIDABLE_HANDLER		__attribute__((weak, alias("Default_Handler")))

void Default_Handler(void);
void Reset_Handler(void);

void NMI_Handler(void) 						OVERRIDABLE_HANDLER;
void HardFault_Handler(void) 				OVERRIDABLE_HANDLER;
void MemManage_Handler(void) 				OVERRIDABLE_HANDLER;
void BusFault_Handler(void) 				OVERRIDABLE_HANDLER;
void UsageFault_Handler(void) 				OVERRIDABLE_HANDLER;
void SVCall_Handler(void) 					OVERRIDABLE_HANDLER;
void DebugMonitor_Handler(void) 			OVERRIDABLE_HANDLER;
void PendSV_Handler(void) 					OVERRIDABLE_HANDLER;
void Systick_Handler(void) 					OVERRIDABLE_HANDLER;
void WWDG_Handler(void) 					OVERRIDABLE_HANDLER;
void PVD_Handler(void) 						OVERRIDABLE_HANDLER;
void EXTI21_TAMP_STAMP_Handler(void)		OVERRIDABLE_HANDLER;
void EXTI22_RTC_WKUP_Handler(void)			OVERRIDABLE_HANDLER;
void TAMPER_STAMP_Handler(void) 			OVERRIDABLE_HANDLER;
void RTC_WKUP_Handler(void) 				OVERRIDABLE_HANDLER;
void FLASH_Handler(void) 					OVERRIDABLE_HANDLER;
void RCC_Handler(void) 						OVERRIDABLE_HANDLER;
void EXTI0_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI1_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI2_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI3_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI4_Handler(void) 					OVERRIDABLE_HANDLER;
void DMA1_Stream0_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA1_Stream1_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA1_Stream2_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA1_Stream3_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA1_Stream4_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA1_Stream5_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA1_Stream6_Handler(void) 			OVERRIDABLE_HANDLER;
void ADC_Handler(void) 						OVERRIDABLE_HANDLER;
void EXTI9_5_Handler(void) 					OVERRIDABLE_HANDLER;
void TIM1_BRK_TIM9_Handler(void) 			OVERRIDABLE_HANDLER;
void TIM1_UP_Handler(void) 					OVERRIDABLE_HANDLER;
void TIM1_TRG_COM_TIM11_Handler(void) 		OVERRIDABLE_HANDLER;
void TIM1_CC_Handler(void) 					OVERRIDABLE_HANDLER;
void I2C1_EV_Handler(void) 					OVERRIDABLE_HANDLER;
void I2C1_ER_Handler(void) 					OVERRIDABLE_HANDLER;
void I2C2_EV_Handler(void) 					OVERRIDABLE_HANDLER;
void I2C2_ER_Handler(void) 					OVERRIDABLE_HANDLER;
void SPI1_Handler(void) 					OVERRIDABLE_HANDLER;
void SPI2_Handler(void) 					OVERRIDABLE_HANDLER;
void USART1_Handler(void) 					OVERRIDABLE_HANDLER;
void USART2_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI15_10_Handler(void) 				OVERRIDABLE_HANDLER;
void EXTI17_RTC_Alarm_Handler(void)			OVERRIDABLE_HANDLER;
void RTC_Alarm_Handler(void) 				OVERRIDABLE_HANDLER;
void DMA1_Stream7_Handler(void) 			OVERRIDABLE_HANDLER;
void TIM5_Handler(void) 					OVERRIDABLE_HANDLER;
void TIM6_DAC_Handler(void) 				OVERRIDABLE_HANDLER;
void DMA2_Stream0_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA2_Stream1_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA2_Stream2_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA2_Stream3_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA2_Stream4_Handler(void) 			OVERRIDABLE_HANDLER;
void EXTI19_Handler(void) 					OVERRIDABLE_HANDLER;
void DMA2_Stream5_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA2_Stream6_Handler(void) 			OVERRIDABLE_HANDLER;
void DMA2_Stream7_Handler(void) 			OVERRIDABLE_HANDLER;
void USART6_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI20_Handler(void) 					OVERRIDABLE_HANDLER;
void RNG_Handler(void) 						OVERRIDABLE_HANDLER;
void FPU_Handler(void) 						OVERRIDABLE_HANDLER;
void SPI5_Handler(void) 					OVERRIDABLE_HANDLER;
void I2C4_EV_Handler(void) 					OVERRIDABLE_HANDLER;
void I2C4_ER_Handler(void) 					OVERRIDABLE_HANDLER;
void EXTI23_LPTIM1_Handler(void) 			OVERRIDABLE_HANDLER;


/*
 * Refer to Manual RM0401, page 198
 * 		9. Interrupts and events
 * 			9.2 External interrupt/event controller (EXTI)
 * 				Table 39. Vector table
 * https://www.st.com/resource/en/reference_manual/rm0401-stm32f410-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
 */
uint32_t NVIC[] __attribute__((section(".nvic"))) = {
	STACK_START,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	(uint32_t)&MemManage_Handler,
	(uint32_t)&BusFault_Handler,
	(uint32_t)&UsageFault_Handler,
	0,
	0,
	0,
	0,
	(uint32_t)&SVCall_Handler,
	(uint32_t)&DebugMonitor_Handler,
	0,
	(uint32_t)&PendSV_Handler,
	(uint32_t)&Systick_Handler,
	(uint32_t)&WWDG_Handler,
	(uint32_t)&PVD_Handler,
	(uint32_t)&EXTI21_TAMP_STAMP_Handler,
	(uint32_t)&EXTI22_RTC_WKUP_Handler,
	(uint32_t)&FLASH_Handler,
	(uint32_t)&RCC_Handler,
	(uint32_t)&EXTI0_Handler,
	(uint32_t)&EXTI1_Handler,
	(uint32_t)&EXTI2_Handler,
	(uint32_t)&EXTI3_Handler,
	(uint32_t)&EXTI4_Handler,
	(uint32_t)&DMA1_Stream0_Handler,
	(uint32_t)&DMA1_Stream1_Handler,
	(uint32_t)&DMA1_Stream2_Handler,
	(uint32_t)&DMA1_Stream3_Handler,
	(uint32_t)&DMA1_Stream4_Handler,
	(uint32_t)&DMA1_Stream5_Handler,
	(uint32_t)&DMA1_Stream6_Handler,
	(uint32_t)&ADC_Handler,
	0,
	0,
	0,
	0,
	(uint32_t)&EXTI9_5_Handler,
	(uint32_t)&TIM1_BRK_TIM9_Handler,
	(uint32_t)&TIM1_UP_Handler,
	(uint32_t)&TIM1_TRG_COM_TIM11_Handler,
	(uint32_t)&TIM1_CC_Handler,
	0,
	0,
	0,
	(uint32_t)&I2C1_EV_Handler,
	(uint32_t)&I2C1_ER_Handler,
	(uint32_t)&I2C2_EV_Handler,
	(uint32_t)&I2C2_ER_Handler,
	(uint32_t)&SPI1_Handler,
	(uint32_t)&SPI2_Handler,
	(uint32_t)&USART1_Handler,
	(uint32_t)&USART2_Handler,
	0,
	(uint32_t)&EXTI15_10_Handler,
	(uint32_t)&EXTI17_RTC_Alarm_Handler,
	0,
	0,
	0,
	0,
	0,
	(uint32_t)&DMA1_Stream7_Handler,
	0,
	0,
	(uint32_t)&TIM5_Handler,
	0,
	0,
	0,
	(uint32_t)&TIM6_DAC_Handler,
	0,
	(uint32_t)&DMA2_Stream0_Handler,
	(uint32_t)&DMA2_Stream1_Handler,
	(uint32_t)&DMA2_Stream2_Handler,
	(uint32_t)&DMA2_Stream3_Handler,
	(uint32_t)&DMA2_Stream4_Handler,
	0,
	(uint32_t)&EXTI19_Handler,
	0,
	0,
	0,
	0,
	0,
	(uint32_t)&DMA2_Stream5_Handler,
	(uint32_t)&DMA2_Stream6_Handler,
	(uint32_t)&DMA2_Stream7_Handler,
	(uint32_t)&USART6_Handler,
	0,
	0,
	0,
	0,
	(uint32_t)&EXTI20_Handler,
	0,
	0,
	0,
	(uint32_t)&RNG_Handler,
	(uint32_t)&FPU_Handler,
	0,
	0,
	0,
	(uint32_t)&SPI5_Handler,
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
	(uint32_t)&I2C4_EV_Handler,
	(uint32_t)&I2C4_ER_Handler,
	(uint32_t)&EXTI23_LPTIM1_Handler
};

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void) {
	// Copy .data section to SRAM
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	uint8_t *pDestination = (uint8_t*)&_sdata;	// SRAM
	uint8_t *pSource - (uint8_t*)&_etext;	// FLASH

	asm volatile(
		"mov r0, %[pDestination]\n"		// Load the start address of the destination into r0
		"mov r1, %[size]\n"				// Load the size of the copy into r1
		"mov r2, #0\n"					// Initialize r2 with zero

		"copy_loop:\n"
			"cmp r1, #0\n"				// Compare the size with zero
			"beq copy_end\n"			// Branch to copy_end if size is zero
			"ldrb r3, [%[pSource]]\n"	// Load a byte from the source address
			"strb r3, [r0], #1\n"		// Store the byte to the destination address and increment the destination pointer
			"subs r1, r1, #1\n"			// Subtract 1 from size
			"b copy_loop\n"				// Branch back to copy_loop

		"copy_end:\n"
		:
		: [pDestination] "r" (pDestination), [size] "r" (size), [pSource] "r" (pSource)
		: "r0", "r1", "r2", "r3"
	);

	// Initialize .bss section to 0
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	pDestination = (uint8_t*)&_sbss;
	
	asm volatile(
		"mov r0, %[dest]\n"				// Load the start address of .bss section into r0
		"mov r1, %[size]\n"				// Load the size of .bss section into r1
		"mov r2, #0\n"					// Initialize r2 with zero

		"loop:\n"
			"cmp r1, #0\n"				// Compare the size with zero
			"beq end\n"					// Branch to end if size is zero
			"strb r2, [r0], #1\n"		// Store byte zero at the current address and increment the address
			"subs r1, r1, #1\n"			// Subtract 1 from size
			"b loop\n"					// Branch back to the loop

		"end:\n"
		:
		: [dest] "r" (pDestination), [size] "r" (size)
		: "r0", "r1", "r2"
	);

	// Call program entry point
	main();
}

void Default_Handler(void) {
	while(1);
}