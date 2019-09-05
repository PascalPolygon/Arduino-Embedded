#include <ServoPWM.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

ServoPWM servoPWM;
void setup() {
  Serial.begin(9600);
  servoPWM.servo_write(90);
  //set_angle(0);// put your setup code here, to run once:

}

void set_angle(int pos)
{
  pos = map(pos, 0, 180, 1, 14);
  OCR1A = (1050) + (pos * ((4889 - 1050) / (180)));
  //1050, 4889
}

void loop() {
 /* int i = 0;
  
  for(i= 0; i <= 180; i++)
  {
    servoPWM.servo_write(i);
    delay(50);
    Serial.println(i);
  }
  for(i = 180; i >= 0; i--)
  {
    servoPWM.servo_write(i);
    //set_angle(i);
    delay(50);
    Serial.println(i);
  }*/
  
}
