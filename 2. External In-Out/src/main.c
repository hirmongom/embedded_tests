/*
 * @FILENAME:          main.c
 *
 * @DESCRIPTION:       Intermitently lights a LED conected to PE1. There is a push button
 *                     connected in PE0 and, while it is pressed, the LED whil turn on and off
 *                     faster.
 *
 * @AUTHOR:            Hiram Montejano Gómez
 * 
 * @STARTING DATE:     10/08/2021
 */

#include <TM4C123GH6PM.h>

void PortE_Init(void);
void delayms(int milisec);

int main(void)
{
  PortE_Init();

  while(1)
  {
    while(!(GPIOE->DATA & (1)))
    {
      GPIOE->DATA |= (1<<1);
      delayms(200);
      GPIOE->DATA &= ~(1<<1);
      delayms(200);
    }
    while(GPIOE->DATA & (1))
    {
      GPIOE->DATA |= (1<<1);
      delayms(50);
      GPIOE->DATA &= ~(1<<1);
      delayms(50);
    }
  }

  return 0;
}

void PortE_Init(void)
/*
 * @BRIEF:            Initializes port E
 *
 * @ARGUMENTS:        None
 *
 * @RETURNS:          None
 */
{
  SYSCTL->RCGCGPIO |= 0x10;

  GPIOE->DIR |= 0x02;
  GPIOE->DEN |= 0x03;
}

void delayms(int milisec)
/*
 * @BRIEF:            Generates a delay for a set amount of time
 *
 * @ARGUMENTS:        milisec: Amount of miliseconds the delay is going to take (Not precise at all)
 *
 * @RETURNS:          None
 */
{
  SysTick->LOAD = SystemCoreClock / 1000 -1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //0101
  
  for(int i = 0; i < milisec; i++)
  {
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
  }

  SysTick->CTRL=0;
}