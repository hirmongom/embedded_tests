/*
 * @FILENAME:           main.c
 *
 * @DESCRIPTION:        This application "accurately" (lol no) measures distance
 *                      and lights up a series of LEDs based on distance measured.
 *
 * @HARDWARE:           - PB1 -> HC-SR04 ultrasonic sensor (Trigger)
 *                      - PB6 -> HC-SR04 ultrasonic sensor (Echo)
 *
 *                      - PE1 ->  LED 1
 *                      - PE2 ->  LED 2
 *                      - PE3 ->  LED 3
 *                      - PE4 ->  LED 4
 *                      - PE5 ->  LED 5
 *
 * @AUTHOR:             Hiram Montejano Gómez
 * 
 * @STARTING DATE:      15/08/2021
 *
 * @ENDING DATE:        15/08/2021
 */

#include <TM4C123GH6PM.h>
#include <stdio.h>

void delayms(int milisec);
void system_Init(void);
void portE_Init(void);
void portB_Init(void);
void Timer0A_Init(void);
uint32_t Timer0A_CaptureWaveTime(void);
void Timer1A_delay10microsec(void);

int main(void)
{
  system_Init();
  portE_Init();
  portB_Init();
  Timer0A_Init();

  uint32_t wave_time;
  uint32_t distance;

  while(1)
  {

    // Send ultrasonic wave for 10 microseconds
    GPIOB->DATA |= 0x02;                          // Start sending wave
    Timer1A_delay10microsec();                    // Wait 10 microseconds    
    GPIOB->DATA &= ~0x02;                         // Stop sending wave

    wave_time = Timer0A_CaptureWaveTime();        // Store time it took for the wave to travel
    distance = (wave_time * 10625)/10000000;      // Convert time traveled into centimeters traveled

    if(250 < distance)
    {
      GPIOE->DATA &= ~0x3E;     // Turn off all LEDs
    }
    else if((250 >= distance) && (distance > 200))
    {
      GPIOE->DATA |= 0x02;      // Turn on first LED
      GPIOE->DATA &= 0x02;      // Turn off the other LEDs
    }
    else if((200 >= distance) && (distance > 150))
    {
      GPIOE->DATA |= 0x06;      // Turn on the first 2 LEDs
      GPIOE->DATA &= 0x06;      // Turn off the other LEDs
    }
    else if((150 >= distance) && (distance > 100))
    {
      GPIOE->DATA |= 0x0E;      // Turn on the first 3 LEDs
      GPIOE->DATA &= 0x0E;      // Turn off the other LEDs
    }
    else if((100 >= distance) && (distance > 50))
    {
      GPIOE->DATA |= 0x1E;      // Turnn on the first 4 LEDs
      GPIOE->DATA &= 0x1E;      // Turn off the other LEDs
    }
    else if((50 >= distance) && (distance > 1))
    {
      GPIOE->DATA |= 0x3E;      // Turn on all LEDs
    }

    delayms(100);
  }

  return 0;
}

void system_Init(void)
/*
 * @BRIEF:          Initializes system and provides clock to the necessary modules or ports
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  SYSCTL->RCGCGPIO |=  0x12;                // Enable and provide clock to ports B and E in run mode
  SYSCTL->RCGCTIMER |= 0x03;                // Enable and provide clock to timer modules 0 and 1
}

void portE_Init(void)
/*
 * @BRIEF:          Initializes port E
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  GPIOE->DIR |= 0x3E;                       // Set directions of pins PE(1:5) as output
  GPIOE->DEN |= 0x3E;                       // Enable digital function for pins PE(1:5)
}

void portB_Init(void)
/*
 * @BRIEF:          Initializes port B
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  GPIOB->DIR &= ~0x40;                      // Define PB6 (Echo) as input
  GPIOB->DIR |= 0x02;                       // Define PB1 (Trigger) as output
  GPIOB->DEN |= 0x42;                       // Enable digital function for pins PB(1,6)

  GPIOB->AFSEL |= 0x40;                     // Enable alternate function for PB6
  GPIOB->PCTL &= ~0x0F00000;                // Disables all alternate functions in PB6
  GPIOB->PCTL |= 0x07000000;                // Enables T0CCP0 alternate function in PB6
}

void Timer0A_Init(void)
/*
 * @BRIEF:          Initializes timer module 0, subtimer A (T0A) for input edge time mode
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  TIMER0->CTL &= ~0x01;                     // Disable timer T1A during configuration
  TIMER0->CFG |= 0x04;                      // Selects the 16-bit timer configuration

  TIMER0->TAMR |= 0x17;                     // Enable count-up, edge-time and capture mode for T1A
  
  TIMER0->CTL |= 0x0C;                      // Capture rising and falling edges on PB6
  TIMER0->CTL |= 0x01;                      // Enable timer T1A
}

uint32_t Timer0A_CaptureWaveTime(void)
/*
 * @BRIEF:          Measures the time it takes for the ultrasonic wave to travel forth
 *                  and back to the sensor.
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        Time measured
 */
{
  int rising_edge, falling_edge;

  while(1)
  {
    TIMER0->ICR |= 0x04;                      // Clear T0A capture mode event interrupt flag
    while((TIMER0->RIS & 0x04) == 0)          // Wait for rising edge

    if(GPIOB->DATA & (0x40))
    {
      rising_edge = TIMER0->TAR;              // Save timestamp of when rising edge occurs

      TIMER0->ICR |= 0x04;                    // Clear T0A capture mode event interrupt flag

      while((TIMER0->RIS & 0x04) == 0)        // Wait until falling edge event
      falling_edge = TIMER0->TAR;             // Save timestamp of when falling edge occurs

      return (falling_edge - rising_edge);
    }
  }
}

void Timer1A_delay10microsec(void)
/*
 * @BRIEF:          Initializes timer module 1, subtimer A (T1A) for one shot mode
 *                  and counts down for 10 microseconds
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  // Initialize and configure timer
  TIMER1->CTL &= ~0x01;                     // Disable timer T1A during configuration
  TIMER1->CFG |= 0x04;                      // Selects the 16-bit timer configuration

  TIMER1->TAMR |= 0x01;                     // Enable count-down and one-shot mode for T0A

  /*
   * At a CPU frequency of 16MHz means a clock period of
   * 1/16MHz = 62.5ns being fed to TimerA per clock unit.
   * To get a 10 microsecond delay we need: 
   *
   *        10 us *10^3 ns / 62.5 ns = 160 clocks
   */
  TIMER1->TAILR = 160 - 1;                  // Count-down starting value (10 microseconds)

  TIMER1->ICR |= 0x01;                      // Clear T1A time-out interrupt flag

  // Count 10 microseconds
  TIMER1->CTL |= 0x01;                      // Enable T1A

  while((TIMER1->RIS & 0x1) == 0);          // Wait for T1A time-out flag to set
}

//void TIMER1A_Handler(void)
/*
 * @BRIEF:          Interrupt handler for timer module 0, subtimer A
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
/*{


  TIMER1->ICR |= 0x01;                      // T0A time-out interrupt flag bit clear
}*/

void delayms(int milisec)
{
  SysTick->LOAD = SystemCoreClock/1000 -1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //0101
  
  for(int i=0; i<milisec; i++)
  {
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
  }

  SysTick->CTRL=0;
}
