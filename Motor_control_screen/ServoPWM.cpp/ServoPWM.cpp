#define F_CPU 16000000

#include "Arduino.h"
#include "ServoPWM.h"


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

ServoPWM::ServoPWM(void)
{

	TCCR1A |= (1 << WGM11) | (1 << COM1A1);  //PWM, Phase Correct, 9-bit mode of operation
	TCCR1B |= (1 << WGM12) | (1 << WGM13); //Wave form generation mode
	TCCR1B |= (1 << CS11);  //prescaler /1 (no prescaler)

	ICR1 = (F_CPU / 50) - 1; //Input capture register (TOP value)

	DDRB |= (1 << PORTB1); //Setting D9 to output
}

 void ServoPWM::servo_write(int angle)
{
	//DDRB |= (1 << PORTB1);
	//OCR1A = map(angle, 0, 180, 1, 14);
	OCR1A = (1100) + (angle * ((4800 - 1100) / (180)));
	//OCR1A = (2444) + ((angle-90) * ((2444 - 4889) / (180)));
	//OCR1A = (1020) + (angle * ((4889 - 1020) / (180)));
	//delay(20);
	//DDRB &= ~(1 << PORTB1);

}
