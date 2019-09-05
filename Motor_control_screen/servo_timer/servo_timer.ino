// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       servo_timer.ino
    Created:  10/2/2018 11:38:21 PM
    Author:     LAPTOP-CBF8MU40\PascalMawabaDao
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define PULSE_MAX 4800
#define PULSE_MIN 1100
#define PULSE_MID 2950

void setup()
{
  TCCR1A &=~(1 << WGM10); //Disable CTC in register 1
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);  //PWM, Phase Correct, 9-bit mode of operation
  TCCR1B |= (1 << WGM12) | (1 << WGM13); //Wave form generation mode
  TCCR1B |= (1 << CS11); //| (1 << CS10);  //prescaler /1 (no prescaler)
  TCCR1B &=~(1 << CS10); //disable presclaer
  ICR1 =(F_CPU / 50)-1; //Input capture register (TOP value)

  DDRB |= (1 << PORTB1); 

  OCR1A = (1100) + (180 * ((4800 - 1100) / (180)));
}

void loop()
{
  
}
/*int main(void)
{
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);  //PWM, Phase Correct, 9-bit mode of operation
  TCCR1B |= (1 << WGM12) | (1 << WGM13); //Wave form generation mode
  TCCR1B |= (1 << CS11); //| (1 << CS10);  //prescaler /1 (no prescaler)
  TCCR1B |= (1 << CS10);
  ICR1 =(F_CPU / 50)-1; //Input capture register (TOP value)

  DDRB |= (1 << PORTB1); //Setting D9 to output

  while(1)
  {
    OCR1A = (1100) + (90 * ((4800 - 1100) / (180)));
   _delay_ms(100);
  }
  return 0;
}*/
// The setup() function runs once each time the micro-controller starts
