/*
 * @FILENAME:           main.c
 *
 * @DESCRIPTION:        This application receives the temperature of a PC's CPU
 *                      through serial communication (UART) and lights up a series
 *                      of LEDs based on the temperature received of up to 89ºC.
 *
 * @HARDWARE:           PA0 -> UART0 Rx (Built-in)
 *                      PA1 -> UART0 Tx (Built-in)
 *                      PE0 -> Green LED
 *                      PE1 -> Orange LED 1
 *                      PE2 -> Orange LED 2
 *                      PE3 -> Red LED 1
 *                      PE4 -> Red LED 2
 *
 * @AUTHOR:             Hiram Montejano Gómez
 * 
 * @STARTING DATE:      27/08/2021
 *
 * @ENDING DATE:        28/08/2021
 */

#include <TM4C123GH6PM.h>

void UART0_init(void);
void GPIOE_init(void);
void UART0_Handler(void);
unsigned char UART0_Rx(void);
void Temperature_Output(unsigned char temperature);

int main(void)
{
  UART0_init();
  GPIOE_init();

  while(1)
  {
    // Wait for interrupt
  }

  return 0;
}

void UART0_init(void)
/*
 * @BRIEF:          Initializes UART module 0 in GPIO port A.
 *                      - 9600 baud rate
 *                      - Data length of 8 bits
 *                      - One stop bit
 *                      - No parity
 *                      - FIFOs disabled
 *                      - No interrupts
 *
 * @NOTES:
 *    - Baud Rate Divisor (BRD)
 *
 * The BRD has the following relationship with the system clock:
 *      BRD = BRDInteger + BRDFraction = UARTSysClk / (ClkDiv * Baud Rate)
 * where  UARTSysClk is the system clock conected to the UART
 * and    ClkDiv is either 16 (if HSE in UARTCTL register) is clear, or 8 (if HSE is set).
 *
 * The 6-bit fractional number that's loaded into the DIVFRAC bit field in the UARTFBRD register
 * can be calculated with the next formula:
 *      UARTFBRD[DIVFRAC] = (int) (BRDF * 64 + 0'5)    
 *
 * For a baud rate of 115,200:
 *      BRD = 16,000,000 / (16 * 115,200) = 8'6806
 *      UARTFBRD[DRIVFRAC] = (int) (0'6806 * 64 + 0'5) = 44
 */
{
  SYSCTL->RCGCUART |= 0x01;                     // Enable and provide clock to UART 0 in run mode
  SYSCTL->RCGCGPIO |= 0x01;                     // Enable and provide clock to GPIO A in run mode

  GPIOA->AFSEL |= 0x03;                         // Enable alternate function for pins PA(0:1)
  GPIOA->PCTL |= 0x11;                          // Enable U0Rx(PA0) & U0Tx(PA1) alternate functions
  GPIOA->DEN |= 0x03;                           // Set PA(0:1) as digital pins

  UART0->CTL &= ~0x01;                          // Disable UART0 during configuration

  UART0->IBRD |= 0x08;                          // Integer Baud-Rate divisor (8)
  UART0->FBRD |= 0x2C;                          // Fractional Baud-Rate divisor (44)
  UART0->LCRH |= 0x60;                          // Configure serial parameters
  UART0->CC = 0x00;                             // Use Sys clock and divisor factor as clock source

  UART0->ICR|= 0x10;                            // Clear receive interrupt flag
  UART0->IM |= 0x10;                            // Unmask receive interrupt

  NVIC->ISER[0] |= (1<<5);                      // Enable UART0 interrupt in vector table (IRQ5)

  UART0->CTL |= 0x0301;                         // Enable UART module 0, Rx and Tx
}

void GPIOE_init(void)
/*
 * @BRIEF:          Initializes GPIO port E
 */
{
  SYSCTL->RCGCGPIO |= 0x10;                     // Enalbe and provide clock to GPIO E in run mode

  GPIOE->DIR |= 0x1F;                           // Define pins PE(0:4) as outputs
  GPIOE->DEN |= 0x1F;                           // Enable digital I/O for pins PE(0:4)
}

void UART0_Handler(void)
/*
 * @BRIEF:          Handles interrupt in UART module 0
 */
{
  unsigned char echo;

  UART0->ICR |= 0x10;                           // Clear receive interrupt flag

  echo = UART0_Rx();                            // Store value received
  Temperature_Output(echo);
}

unsigned char UART0_Rx(void)
/*
 * @BRIEF:          Receives the value of temperature from the serial port
 *
 * @RETURNS:        Value of temperature in ASCII
 *
 * @NOTES:
 *    - Temperature received
 * The value of temperature received (n) is a 1 digit character that represents a temperature
 * range of:
 *         n*10 : n*10+9.
 * For example a character of '5' represents a temperature of (50:59 ºC)
 *         5*10 : 5*10+9 = 50 : 59
 */
{
  return (unsigned char) UART0->DR;
}

void Temperature_Output(unsigned char temperature)
/*
 * @BRIEF:          Gets the value of temperature and lights the LEDs
 *                  based on that value.
 *
 * @ARGUMENTS:      unsigned_char temperature_UC -> Temperature
 */
{
  if(temperature == '5')              // 50:59 ºC
  {
    GPIOE->DATA |= 0x02;
    GPIOE->DATA &= 0x02;
  }
  else if(temperature == '6')         // 60:69 ºC
  {
    GPIOE->DATA |= 0x06;
    GPIOE->DATA &= 0x06;
  }
  else if(temperature == '7')         // 70:79 ºC
  {
    GPIOE->DATA |= 0x0E;
    GPIOE->DATA &= 0x0E;
  }
  else if(temperature == '8')         // 80:89 ºC
  {
    GPIOE->DATA |= 0x1E;
    GPIOE->DATA &= 0x1E; 
  }
  else                                // < 50 ºC
  {
    GPIOE->DATA |= 0x01;
    GPIOE->DATA &= 0x01;
  }
}