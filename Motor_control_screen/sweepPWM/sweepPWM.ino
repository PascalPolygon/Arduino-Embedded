#include <ServoPWM>

ServoPWM ServoPWM();
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int i = 0
  for (i = 0; i < 180; i++)
  {
    ServoPWM.servo_write(i);
    delay(20);
  }
  for (i = 180; i > 0; i--)
  {
    ServoPWM.servo_write(i);
    delay(20);
  }
  

}
