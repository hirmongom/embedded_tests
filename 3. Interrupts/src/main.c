/*
 * @FILENAME:           main.c
 *
 * @DESCRIPTION:        LED toggled by external interrupt:
 *                        - LED will turn on for "x" seconds if only 1 interrupt triggered
 *                        - LED will turn on until interrupt triggered again if another interrupt
 *                          occurs while the LED is on. (Interrupt happens before the LED turns off
 *                          by the delay)
 *
 * @HARDWARE:           - PE0: Electret microphone
 *                      - PE1: White LED
 *
 * @AUTHOR:             Hiram Montejano Gómez
 * 
 * @STARTING DATE:      10/08/2021
 *
 * @ENDING DATE:        11/08/2021
 */

#include "TM4C123GH6PM.h"

extern void delayms(int milisec);

void PortE_Init(void);
void GPIOE_Handler(void);

int event, delay_flag;

int main(void)
{
  PortE_Init();

  while(1)
  {
    switch(event)
    {
      case 1:
        GPIOE->DATA |= (1<<1);      // Turn on led

        delay_flag = 1;     // Delay starts
        for (unsigned int i = 4000000; (i > 0) && (event == 1); i--) {} 
        delay_flag = 0;     // Delay finishes
        
        if(event == 1)      // If delay has finished normaly, clear the event
        {
          event = 0;
        } 
        break;
      case 2:
        // Do nothing and wait for interrupt to trigger event 3
        break;
      case 3:
        event = 0;     // Clear the event (process completed)
        break;
      default:
        GPIOE->DATA &= ~(1<<1);     // Turn off led
        break;
    }
  }

  return 1;   
}

void PortE_Init(void)
/*
 * @BRIEF:          Initializes port E
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  SYSCTL->RCGCGPIO |= 0x10;             /* Provide clock to port E in Run mode                    */

  GPIOE->DIR |= 0x02;                   /* Define pin 1 as output                                 */
  GPIOE->DIR &= ~0x01;                  /* Define pin 0 as input                                  */
  GPIOE->DEN |= 0x03;                   /* Enable digital I/O for pins 0:1                        */

  /* Configure Interrupt */
  GPIOE->IS &= ~0x01;                   /* Define interrupt in pin 0 as edge-sensitive            */ 
  GPIOE->IBE &= ~0x01;                  /* Interrupt event trigger controlled by IEV register     */
  GPIOE->IEV |= 0x01;                   /* Interrupt in pin 0 triggered by rising edge            */
  GPIOE->ICR |= 0x01;                   /* Clear prior interrupt flags                            */
  GPIOE->IM |= 0x01;                    /* Unmask interrupt in pin 0 (Enable interrupt)           */

  NVIC->IP[1] |= (3<<5);                /* Set interrupt priority to 3                            */
  NVIC->ISER[0] |= (1<<4);              /* Enable port E interrupt IRQ04                          */
}

void GPIOE_Handler(void)
/*
 * @BRIEF:          Handles interrupts in port E
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  if(!delay_flag && !event) {event = 1;}      // If no event is running, trigger event 1
  else if(delay_flag) {event = 2;}      // If event 1 is running, trigger event 2

  if ((event == 2) && !delay_flag) {event = 3;}     // If event 2 is running, trigger event 3

  GPIOE->ICR |= 0x01;           // Clear the interrupt event                                       
  delayms(75);        // Prevent double trigger
}