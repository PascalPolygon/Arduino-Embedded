// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain

#include <stdint.h>
#include "TouchScreen.h"

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 7   // can be a digital pin

int16_t x, y;
TSPoint p;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {
  //pinMode(YP, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(YP), touch, HIGH);
  Serial.begin(9600);
}

void loop(void)
{
  p = ts.getPoint();
  
  if (p.z > ts.pressureThreshhold) {
     x = p.x;
     y = p.y;
     touch();
     //Serial.print("touch\n");
     //Serial.print("X = "); Serial.print(p.x);
     //Serial.print("\tY = "); Serial.print(p.y);
     //Serial.print("\tPressure = "); Serial.println(p.z);
  }

  delay(100);
}

/*(void loop(void) {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
     Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
  }

  delay(100);
}*/

void touch(void)
{
  //TSPoint p = ts.getPoint();
  
  //if (p.z > ts.pressureThreshhold) {
     Serial.print("X = "); Serial.println(p.x);
     Serial.print("\tY = "); Serial.println(p.y);
     //Serial.print("\tPressure = "); Serial.println(p.z);
  //}

  //delay(100);
}
  
