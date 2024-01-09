/*
 * @FILENAME:          main.c
 *
 * @APPLICATION:       Simple GPIO program for Tiva-C TM4123GXL Launchpad
 *
 * @BRIEF:             This program makes use of the in-built switches and leds in the launchpad.
 *                     Based on the input, the led will light up in a different colour:
 *                        - Both switches pressed:    LED red
 *                        - Switch 1 pressed:         LED blue
 *                        - Switch 2 pressed:         LED green
 *
 * @AUTHOR:            Hiram Montejano Gómez
 * 
 * @STARTING DATE:     29 Jun 2021
 */

#include <TM4C123GH6PM.h>

void PortF_Init(void);

int main(void)
{
  PortF_Init();

  while(1)
  {
    switch(GPIOF->DATA & 0x11)
    {
      case 0x00:                                        /* Both switches pressed                  */
        GPIOF->DATA = (1<<1);                           /* LED red                                */
        break;
      case 0x10:                                        /* SW1 pressed                            */
        GPIOF->DATA = (1<<2);                           /* LED blue                               */
        break;
      case 0x01:                                        /* SW2 pressed                            */
        GPIOF->DATA = (1<<3);                           /* LED green                              */
        break;
      default:
        GPIOF->DATA = ((0<<1) | (0<<2) | (0<<3));       /* Clear all outputs (LED off)            */
        break;
    }
  }

  return 0;
}

void PortF_Init(void)
/*
 * @NAME:              void PortF_Init(void)
 *
 * @DESCRIPTION:       Initializes Port F
 *
 * @ARGUMENTS:         None
 * 
 * @RETURNS:           None
 */
{
  SYSCTL->RCGCGPIO = 0x20;        /* Enable and provide clock to Port F in Run mode               */

  GPIOF->LOCK = 0x4C4F434B;       /* Enables write access to the GPIOCR register                  */
  GPIOF->CR = 0x1F;               /* Allow changes to pins 0 to 4 of Port F                       */

  GPIOF->DIR = 0x0E;              /* Set direction of the GPIO pins (1 = output, 0 = input)       */
  GPIOF->PUR = 0x11;              /* Enable pull-up resistors on pins 0 and 4                     */
  GPIOF->DEN = 0x1F;              /* Enable pins 0 to 4 as digital I/O                            */
}
