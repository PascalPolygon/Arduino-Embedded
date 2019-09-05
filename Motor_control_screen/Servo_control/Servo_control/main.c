/*
 * Servo_control.c
 *
 * Created: 9/29/2018 2:29:26 PM
 * Author : PascalMawabaDao
 */ 
//#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define PULSE_MIN 1000  // 1ms pulse for most counterclockwise
#define PULSE_MAX 2000  // 2ms pulse for most clockwise
#define PULSE_MID 1500	// 1.5ms pulse for center

static inline void initialize_timer1(void)
{
	
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);  //PWM, Phase Correct, 9-bit mode of operation
	TCCR1B |= (1 << WGM12) | (1 << WGM13); //Wave form generation mode
	TCCR1B |= (1 << CS11);  //prescaler /1 (no prescaler)
	
	ICR1 = 20000 ; //Input capture register (TOP value)
	//TCCR1A |= (1 << COM1A1); //Direct ouput on PB1/ OC1A
	
	DDRB |= (1 << PORTB1); //Setting D9 to output
}

static inline void showOff(void)
{
	OCR1A = PULSE_MID;
	//printf("Going to middle...\n");
	_delay_ms(5000);
	
	OCR1A = PULSE_MIN;
	_delay_ms(5000);
	OCR1A = PULSE_MAX;
	_delay_ms(5000);
	OCR1A = PULSE_MID;
	_delay_ms(5000);
	DDRB &= ~(1 << PORTB1);
	
}


static inline void servo_write(int angle)
{
	
	  OCR1A = (1019)+angle*((4889-1019)/(180));
	 // if (angle == 90)
		 //OCR1A = ((1019)+angle*((4889-1019)/(180)))-120;
}

int main(void)
{
    /* Replace with your application code */
	
	//uint16_t servoPulseLength;
	//OCR1A = PULSE_MID;
	initialize_timer1();
	//showOff();
	
   /* while (1) 
    {
		servoPulseLength = 1800;
		
		OCR1A = servoPulseLength;
		
		DDRB |= (1 << PORTB1); //re-enable output pin
		
		_delay_ms(1000);
		
		while(TCNT1 < 3000){;}
		
		DDRB &= ~(1 << PORTB1); //disable output pin
    }*/
   int offset = 800;
   int i = 0;
  // int user_anlge;
  // OCR1A = (1019)+user_anlge*(4889-1019)/(90);
  
   /*while(1)
   {
	  
		servo_write(180);
	   _delay_ms(10000);
	  
	    servo_write(90);
	   _delay_ms(10000);
	  
	    servo_write(0);
	   _delay_ms(10000);  
		
		servo_write(0);
   }*/
   while(1)
   {
	      for  (i = 0; i <= 180; i+=10)
	      {
		      servo_write(i);
		      _delay_ms(5000);
	      }
	      
	      _delay_ms(5000);
	      
	      for (i = 180; i >= 0; i-=10)
	      {
		      servo_write(i);
		      _delay_ms(5000);
	      }
	      

   }
   

	
	return 0;
}

