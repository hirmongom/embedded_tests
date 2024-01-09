//*****************************************************************************
//
// startup_TM4C.c - Startup code for use with GNU tools.
//
//*****************************************************************************



#include <stdint.h>
#include "TM4C123GH6PM.h"

//*****************************************************************************
//
// Internal References
//
//*****************************************************************************
void Reset_Handler  (void);
void Default_Handler(void);

//*****************************************************************************
//
// Exception / Interrupt Handlers
//
//*****************************************************************************
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler    (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

// External interrupts
void GPIOA_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOB_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOC_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOD_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOE_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PMW0_FAULT_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_0_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_1_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_2_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void QEI0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC0SS0_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC0SS1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC0SS2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC0SS3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void WDT0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0A_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0B_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1A_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1B_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER2A_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER2B_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP0_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP1_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SYSCTL_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOF_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOG_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOH_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART2_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER3A_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER3B_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void QEI1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void HIB_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USB0_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM0_3_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void UDMA_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void UDMAERR_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1SS0_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1SS1_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1SS2_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1SS3_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOJ_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOK_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOL_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void SSI3_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void UART3_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART6_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void UART7_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER4A_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER4B_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER5A_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER5B_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER0A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER0B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER1A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER1B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER2A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER2B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER3A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER3B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER4A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER4B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER5A_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void WTIMER5B_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C4_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C5_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOM_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPION_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void QEI2_Handler           (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP0_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP1_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP2_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP3_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP4_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP5_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP6_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOP7_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ0_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ1_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ2_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ3_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ4_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ5_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ6_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOQ7_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOR_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIOS_Handler          (void) __attribute__ ((weak, alias("Default_Handler")));
void PMW1_0_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_1_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_2_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_3_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void PWM1_FAULT_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
static uint32_t pui32Stack[512];

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".vectors")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)pui32Stack + sizeof(pui32Stack)),  // The initial stack pointer
                                            
    Reset_Handler,             //      Reset Handler
    NMI_Handler,               // -14: NMI Handler
    HardFault_Handler,         // -13: Hard Fault Handler
    MemManage_Handler,         // -12: MPU Fault Handler
    BusFault_Handler,          // -11: Bus Fault Handler
    UsageFault_Handler,        // -10: Usage Fault Handler
    0,
    0,                         //      Reserved
    0,                         //      Reserved
    0,                         //      Reserved
    SVC_Handler,               // -5:  SVCall Handler
    DebugMon_Handler,          // -4:  Debug Monitor Handler
    0,                         //      Reserved */
    PendSV_Handler,            // -2:  PendSV Handler
    SysTick_Handler,           // -1:  SysTick Handler


    GPIOA_Handler,             // 0: GPIO Port A
    GPIOB_Handler,             // 1: GPIO Port B
    GPIOC_Handler,             // 2: GPIO Port C
    GPIOD_Handler,             // 3: GPIO Port D
    GPIOE_Handler,             // 4: GPIO Port E
    UART0_Handler,             // 5: UART0 Rx and Tx
    UART1_Handler,             // 6: UART1 Rx and Tx
    SSI0_Handler,              // 7: SSI0 Rx and Tx
    I2C0_Handler,              // 8: I2C0 Master and Slave
    PMW0_FAULT_Handler,        // 9: PWM Fault
    PWM0_0_Handler,            // 10: PWM Generator 0
    PWM0_1_Handler,            // 11: PWM Generator 1
    PWM0_2_Handler,            // 12: PWM Generator 2
    QEI0_Handler,              // 13: Quadrature Encoder 0
    ADC0SS0_Handler,           // 14: ADC Sequence 0
    ADC0SS1_Handler,           // 15: ADC Sequence 1
    ADC0SS2_Handler,           // 16: ADC Sequence 2
    ADC0SS3_Handler,           // 17: ADC Sequence 3
    WDT0_Handler,              // 18: Watchdog timer
    TIMER0A_Handler,           // 19: Timer 0 subtimer A
    TIMER0B_Handler,           // 20: Timer 0 subtimer B
    TIMER1A_Handler,           // 21: Timer 1 subtimer A
    TIMER1B_Handler,           // 22: Timer 1 subtimer B
    TIMER2A_Handler,           // 23: Timer 2 subtimer A
    TIMER2B_Handler,           // 24: Timer 2 subtimer B
    COMP0_Handler,             // 25: Analog Comparator 0
    COMP1_Handler,             // 26: Analog Comparator 1
    COMP2_Handler,             // 27: Analog Comparator 2
    SYSCTL_Handler,            // 28: System Control (PLL, OSC, BO)
    FLASH_Handler,             // 29: FLASH Control
    GPIOF_Handler,             // 30: GPIO Port F
    GPIOG_Handler,             // 31: GPIO Port G
    GPIOH_Handler,             // 32: GPIO Port H
    UART2_Handler,             // 33: UART2 Rx and Tx
    SSI1_Handler,              // 34: SSI1 Rx and Tx
    TIMER3A_Handler,           // 35: Timer 3 subtimer A
    TIMER3B_Handler,           // 36: Timer 3 subtimer B
    I2C1_Handler,              // 37: I2C1 Master and Slave
    QEI1_Handler,              // 38: Quadrature Encoder 1
    CAN0_Handler,              // 39: CAN0
    CAN1_Handler,              // 40: CAN1
    CAN2_Handler,              // 41: CAN2
    0,                         // 42: Reserved
    HIB_Handler,               // 43: Hibernate
    USB0_Handler,              // 44: USB0
    PWM0_3_Handler,            // 45: PWM Generator 3
    UDMA_Handler,              // 46: uDMA Software Transfer
    UDMAERR_Handler,           // 47: uDMA Error
    ADC1SS0_Handler,           // 48: ADC1 Sequence 0
    ADC1SS1_Handler,           // 49: ADC1 Sequence 1
    ADC1SS2_Handler,           // 50: ADC1 Sequence 2
    ADC1SS3_Handler,           // 51: ADC1 Sequence 3
    0,                         // 52: Reserved
    0,                         // 53: Reserved
    GPIOJ_Handler,             // 54: GPIO Port J
    GPIOK_Handler,             // 55: GPIO Port K
    GPIOL_Handler,             // 56: GPIO Port L
    SSI2_Handler,              // 57: SSI2 Rx and Tx
    SSI3_Handler,              // 58: SSI3 Rx and Tx
    UART3_Handler,             // 59: UART3 Rx and Tx
    UART4_Handler,             // 60: UART4 Rx and Tx
    UART5_Handler,             // 61: UART5 Rx and Tx
    UART6_Handler,             // 62: UART6 Rx and Tx
    UART7_Handler,             // 63: UART7 Rx and Tx
    0,                         // 64: Reserved
    0,                         // 65: Reserved
    0,                         // 66: Reserved
    0,                         // 67: Reserved
    I2C2_Handler,              // 68: I2C2 Master and Slave
    I2C3_Handler,              // 69: I2C3 Master and Slave
    TIMER4A_Handler,           // 70: Timer 4 subtimer A
    TIMER4B_Handler,           // 71: Timer 4 subtimer B
    0,                         // 72: Reserved
    0,                         // 73: Reserved
    0,                         // 74: Reserved
    0,                         // 75: Reserved
    0,                         // 76: Reserved
    0,                         // 77: Reserved
    0,                         // 78: Reserved
    0,                         // 79: Reserved
    0,                         // 80: Reserved
    0,                         // 81: Reserved
    0,                         // 82: Reserved
    0,                         // 83: Reserved
    0,                         // 84: Reserved
    0,                         // 85: Reserved
    0,                         // 86: Reserved
    0,                         // 87: Reserved
    0,                         // 88: Reserved
    0,                         // 89: Reserved
    0,                         // 90: Reserved
    0,                         // 91: Reserved
    TIMER5A_Handler,           // 92: Timer 5 subtimer A
    TIMER5B_Handler,           // 93: Timer 5 subtimer B
    WTIMER0A_Handler,          // 94: Wide Timer 0 subtimer A
    WTIMER0B_Handler,          // 95: Wide Timer 0 subtimer B
    WTIMER1A_Handler,          // 96: Wide Timer 1 subtimer A
    WTIMER1B_Handler,          // 97: Wide Timer 1 subtimer B
    WTIMER2A_Handler,          // 98: Wide Timer 2 subtimer A
    WTIMER2B_Handler,          // 99: Wide Timer 2 subtimer B
    WTIMER3A_Handler,          // 100: Wide Timer 3 subtimer A
    WTIMER3B_Handler,          // 101: Wide Timer 3 subtimer B
    WTIMER4A_Handler,          // 102: Wide Timer 4 subtimer A
    WTIMER4B_Handler,          // 103: Wide Timer 4 subtimer B
    WTIMER5A_Handler,          // 104: Wide Timer 5 subtimer A
    WTIMER5B_Handler,          // 105: Wide Timer 5 subtimer B
    FPU_Handler,               // 106: FPU
    0,                         // 107: Reserved
    0,                         // 108: Reserved
    I2C4_Handler,              // 109: I2C4 Master and Slave
    I2C5_Handler,              // 110: I2C5 Master and Slave
    GPIOM_Handler,             // 111: GPIO Port M
    GPION_Handler,             // 112: GPIO Port N
    QEI2_Handler,              // 113: Quadrature Encoder 2
    0,                         // 114: Reserved
    0,                         // 115: Reserved
    GPIOP0_Handler,            // 116: GPIO Port P (Summary or P0)
    GPIOP1_Handler,            // 117: GPIO Port P1
    GPIOP2_Handler,            // 118: GPIO Port P2
    GPIOP3_Handler,            // 119: GPIO Port P3
    GPIOP4_Handler,            // 120: GPIO Port P4
    GPIOP5_Handler,            // 121: GPIO Port P5
    GPIOP6_Handler,            // 122: GPIO Port P6
    GPIOP7_Handler,            // 123: GPIO Port P7
    GPIOQ0_Handler,            // 124: GPIO Port Q (Summary or Q0)
    GPIOQ1_Handler,            // 125: GPIO Port Q1
    GPIOQ2_Handler,            // 126: GPIO Port Q2
    GPIOQ3_Handler,            // 127: GPIO Port Q3
    GPIOQ4_Handler,            // 128: GPIO Port Q4
    GPIOQ5_Handler,            // 129: GPIO Port Q5
    GPIOQ6_Handler,            // 130: GPIO Port Q6
    GPIOQ7_Handler,            // 131: GPIO Port Q7
    GPIOR_Handler,             // 132: GPIO Port R
    GPIOS_Handler,             // 133: GPIO Port S
    PMW1_0_Handler,            // 134: PWM 1 Generator 0
    PWM1_1_Handler,            // 135: PWM 1 Generator 1
    PWM1_2_Handler,            // 136: PWM 1 Generator 2
    PWM1_3_Handler,            // 137: PWM 1 Generator 3
    PWM1_FAULT_Handler,        // 138: PWM 1 Fault
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bssstart___;
extern uint32_t __bss_end__;

//*****************************************************************************
//
// Reset Handler
//
//*****************************************************************************
void Reset_Handler(void)
{
    uint32_t *pui32Src, *pui32Dest;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pui32Src = &__etext;
    for(pui32Dest = &__data_start__; pui32Dest < &__data_end__; )
    {
        *pui32Dest++ = *pui32Src++;
    }

    //
    // Zero fill the bss segment.
    //
    __asm("    ldr     r0, =__bss_start__\n"
          "    ldr     r1, =__bss_end__\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// Hard Fault Handler
//
//*****************************************************************************
void HardFault_Handler(void)
{
  while(1);
}

//*****************************************************************************
//
// Default Handler
//
//*****************************************************************************
void Default_Handler(void)
{
  while(1);
}