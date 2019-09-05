#ifndef ServoPWM_h
#define ServoPWM_h

#include "Arduino.h"



/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>*/

class ServoPWM
{
  public:
    ServoPWM(void);
    void servo_write(int angle);
  private:
    int _angle;
};

#endif
