/*
 * @FILENAME:           main.c
 *
 * @DESCRIPTION:        This application controls an array of LEDs
 *                      and turns on a length of them based on
 *                      the input from a potentiometer.
 *
 * @HARDWARE:           - PE0 ->  Potentiometer
 *                      - PE1 ->  Green LED
 *                      - PE2 ->  Blue LED
 *                      - PE3 ->  White LED
 *                      - PE4 ->  Yellow LED
 *                      - PE5 ->  Red LED
 *
 *                      The difference with the last application is that instead
 *                      of using a polling method (which is a waste of microcontroller
 *                      processing time and resources), we use the ADC interrupt
 *                      handler to read the conversion value.
 *
 * @AUTHOR:             Hiram Montejano Gómez
 * 
 * @STARTING DATE:      14/08/2021
 *
 * @ENDING DATE:        14/08/2021
 */

#include <TM4C123GH6PM.h>

void PortE_Init(void);
void ADC0SS3_Handler(void);

volatile unsigned int adc_value;

int main(void)
{

  PortE_Init();

  while(1)
  {
    if(adc_value < 680)
    {
      GPIOE->DATA &= ~0x3E;     // Turn off all LEDs
    }
    else if((680 <= adc_value) && (adc_value < 1360))
    {
      GPIOE->DATA |= 0x02;      // Turn on first LED
      GPIOE->DATA &= 0x02;      // Turn off the other LEDs
    }
    else if((1360 <= adc_value) && (adc_value < 2040))
    {
      GPIOE->DATA |= 0x06;      // Turn on the first 2 LEDs
      GPIOE->DATA &= 0x06;      // Turn off the other LEDs
    }
    else if((2040 <= adc_value) && (adc_value < 2720))
    {
      GPIOE->DATA |= 0x0E;      // Turn on the first 3 LEDs
      GPIOE->DATA &= 0x0E;      // Turn off the other LEDs
    }
    else if((2720 <= adc_value) && (adc_value < 3400))
    {
      GPIOE->DATA |= 0x1E;      // Turnn on the first 4 LEDs
      GPIOE->DATA &= 0x1E;      // Turn off the other LEDs
    }
    else if(3400 < adc_value)
    {
      GPIOE->DATA |= 0x3E;      // Turn on all LEDs
    }
  }

  return 0;
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
  SYSCTL->RCGCGPIO |= 0x10;               // Enable an provide clock to port E in run mode
  SYSCTL->RCGCADC |= 0x01;                // Enable and provide clock for ADC module 0 (ADC0)

  GPIOE->DIR |= 0x3E;                     // Set directions of pins PE1:5 to output
  GPIOE->AFSEL |= 0x01;                   // Enable alternate function for pin PE0 (AIN3)
  GPIOE->DEN |= 0x3E;                     // Enable digital function for pins PE1:5
  GPIOE->DEN &= ~0x01;                    // Disable digital function for pin PE0 (AIN3)
  GPIOE->AMSEL |= 0x01;                   // Enable analog function for pin PE0 (AIN3)

  ADC0->ACTSS &= ~(1<<3);                 // Disable Sample Sequencer 3 (SS3) during configuration
  ADC0->EMUX &= ~0xF000;                  // Conversion event trigger initialized by software
  ADC0->SSMUX3 |= 0x03;                    // Get input sample from channel AIN3 (PE0)
  ADC0->SSCTL3 |= 0x06;                   // Take sample one at a time, set flag at first sample

  ADC0->IM |= (1<<3);                     // Unmask ADC0 SS3 interrupt
  NVIC->ISER[0] |= (1<<17);               // Enable interrupt for ADC0 SS3 (IRQ17)
  ADC0->ACTSS |= (1<<3);                  // Enable SS3 logic 
  ADC0->PSSI |= (1<<3);                   // Enable conversion or start sampling data
}

void ADC0SS3_Handler(void)
/*
 * @BRIEF:          Interrupt handler for ADC0 SS3
 *                  Reads the result from the Analog to Digital Converter
 *                  and stores it in the global variable adc_value
 *
 * @ARGUMENTS:      None
 *
 * @RETURNS:        None
 */
{
  adc_value = ADC0->SSFIFO3;              // Read conversion result from SS3 FIFO
  ADC0->ISC |= 0x08;                      // Clear "conversion completed" interrupt flag
  ADC0->PSSI |= (1<<3);                   // Enable conversion or start sampling data
}