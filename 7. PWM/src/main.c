/*
 * @FILENAME:           main.c
 *
 * @DESCRIPTION:        This application dims a green LED by making use of PWM.
 *                      It has 2 push buttons to either increase or decrease brightness
 *                      and a latching switch that triggers an emergency stop.
 *
 *                      (I was planning to control the speed of a DC motor
 *                      in this application, but since this is the first time
 *                      I've delved into PWM, I didn't manage to make it work,
 *                      so I'm just dimming a LED instead)
 *
 * @HARDWARE:           - PB0 -> Latching switch (SW0)
 *                      - PB1 -> Increase brightness push button (SW1)
 *                      - PB2 -> Decrease brightness push button (SW2)
 *                      - PB6 -> Green LED
 *
 * @AUTHOR:             Hiram Montejano Gómez
 * 
 * @STARTING DATE:      19/08/2021
 *
 * @ENDING DATE:        19/08/2021
 */

#include <TM4C123GH6PM.h>

void portB_init(void);
void GPIOB_Handler(void);
void delayms(int milisec);

#define         MIN_DC           799           // Minimum duty cycle value
#define         MAX_DC           400           // Maximum duty cycle value (Max brightness)

int main(void)
{
  portB_init();

  int duty_cycle = MIN_DC;

  while(1)
  {
    if((GPIOB->DATA & 0x02) && (duty_cycle > MAX_DC))       // if SW1 pressed
    {
      // Increase duty cycle (%)
      duty_cycle -= 1;                                      // Increase brightness
    }
    else if((GPIOB->DATA & 0x04) && (duty_cycle < MIN_DC))  // if SW2 pressed
    {
      // Decrease duty_cycle (%)
      duty_cycle += 1;                                      // Decrease brightness
    }

    PWM0->_0_CMPA = duty_cycle;                             // Update duty cycle

    delayms(1);
  }

  return 0;
}

void portB_init(void)
/*
 * @BRIEF:          Initializes port B:
 *                      - PWM module 0 generator 0 (PB6)
 *                      - GPIO PB(0:2)
 *                      - Interrupt PB0
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  SYSCTL->RCGCPWM |= 0x01;                    // Enable and provide clock to PWM module 0
  SYSCTL->RCGCGPIO |= 0x02;                   // Enable and provide clock to GPIO port B

  SYSCTL->RCC |= (1<<20);                     // Enable PWM clock divider function
  SYSCTL->RCC &= ~0x00010000;                 // Use pre-divider value of 2

  GPIOB->DIR |= 0x40;                         // Define PB6 as output
  GPIOB->DIR &= ~0x07;                        // Define PB(0:2) as input
  GPIOB->AFSEL |= 0x40;                       // Enable alternate function in PB6
  GPIOB->PCTL &= ~0x0F000000;                 // Clear alternate functions in PB6
  GPIOB->PCTL |= 0x04000000;                  // Enable M0PWM0 alternate funciton in PB6
  
  GPIOB->IS &= ~0x01;                         // Define interrupt in PB0 as edge-sensitive
  GPIOB->IBE &= ~0x01;                        // Interrupt event trigger controlled by IEV register
  GPIOB->IEV |= 0x01;                         // Interrupt in PB0 triggered by rising edge
  GPIOB->ICR |= 0x01;                         // Clear prior interrupt flags
  GPIOB->IM |= 0x01;                          // Unmask interrupt in PB0 (Enable interrupt)
  NVIC->ISER[0] |= (1<<1);                    // Enable port E interrupt IRQ01

  GPIOB->DEN |= 0x47;                         // Enable digital fucntion in PB(0:2,6)

  PWM0->_0_CTL &= ~0x01;                      // Disable PWM module 0 generator 0
  PWM0->_0_CTL &= ~0x02;                      // Select count-down mode

  PWM0->_0_GENA |= 0x0000008C;                // Action for Cnt==0,Cnt==LOAD,CmpA down: invert pwmA
  PWM0->_0_LOAD |= 0x320;                     // Set load value of 800 for a Freq of 10KHz
  PWM0->_0_CMPA |= 0x320 - 1;                 // Set duty cycle to minimum value (799)

  PWM0->_0_CTL |= 0x01;                       // Start timers in PWM generator 0
  PWM0->ENABLE |= 0x01;                       // Enable PWM0A
}

void GPIOB_Handler(void)
/*
 * @BRIEF:          Handles the execution of an interrupt in port B.
 *                  The only pin that triggers the interrupt is PB0 (latching switch),
 *                  it will trigger an emergency stop that will stop the motor.
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  PWM0->_0_CMPA |= MIN_DC;
}

void delayms(int milisec)
/*
 * @BRIEF:          Generates a delay for a defined amount of time.
 *                  Calculations based on a 16MHz system clock frequency
 *
 * @ARGUMENTS:      - int milisec -> Duration of the delay in miliseconds
 *
 * @RETURNS:        None
 */
{
  int i, j;

  for(i = 0; i < milisec; i++)
  {
    for(j = 0; j < 160000; j++)
    {
      // Do nothing
    }
  }
}