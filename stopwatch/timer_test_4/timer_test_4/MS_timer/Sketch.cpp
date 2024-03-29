﻿/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <MsTimer2.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void flash();
void stateChange();
//End of Auto generated function prototypes by Atmel Studio



int pinA = 9; // segment 11
int pinB = 8; // segment 7
int pinC = 7; // segment 4
int pinD = 6; // segment 2
int pinE = 5; // segment 1
int pinF = 4; // segment 10
int pinG = 3; // segment 5
int pinDecimal = 0; // D5/D6
   
int pinD1 = 10; // digit 1
int pinD2 = 11; // digit 2
int pinD3 = 12; // digit 3
int pinD4 = 13; // digit 4

//int num = 0;
int i = 0;
int j = 0;
int k = 0;
int l = 0;

bool c1 = false;  //Conditionals for updating 
bool c2 = false;
bool c3 = false;
bool c4 = false;

/*int HUNS = 0;
int TENS = 0;
int TWOS = 0;
int ONES = 0;*/

int huns = 0;
  int tens = 0;
  int twos = 0;
  int ones = 0;

int timedelay = 5;

int pbIn = 2;
volatile int state = LOW;

void disp(int num, int digit);

void flash() {
  
 if (state == LOW)
 {
  huns = i%10;
  //HUNS = huns;
  i++;
  c1 = i>0?true:false;
  if (huns == 0 && c1 == true)
  {
      c1 = true ;
     tens = j%10;
     j++;
     c2 = j>0?true:false;
     if (tens == 0 && c2 == true)
     {
      c2 = true;
       twos = k%10;
       k++;
       c3 = k>0?true:false;
       if (twos == 0 && c3 == true)
       {
          c3 = true;
          ones = l%10;
          l++;
       }
     }
  }
 }
}
  

void setup() {
  //Serial.begin(9600); 
  
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  pinMode(pinDecimal, OUTPUT);

  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(pinD3, OUTPUT);
  pinMode(pinD4, OUTPUT);

  pinMode(pbIn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pbIn), stateChange, RISING);

  MsTimer2::set(10, flash); // 500ms period
  MsTimer2::start();

}

void loop() 
{
  //timedelay =(timedelay+HUNS)*4;
  disp(huns, 4);
  delay(timedelay);
  disp(tens, 3);
  delay(timedelay);
  disp(twos, 2);
  delay(timedelay);
  disp(ones, 1);
  delay(timedelay);
}

void stateChange()
{
  state =! state;
}


void disp(int num, int digit)
{

 // turnOff();
  if (digit == 1)
  {
    digitalWrite(pinD1, LOW); 
    digitalWrite(pinD2, HIGH);
    digitalWrite(pinD3, HIGH);
    digitalWrite(pinD4, HIGH);
  }
  else if (digit == 2)
  {
    digitalWrite(pinD1, HIGH); 
    digitalWrite(pinD2, LOW);
    digitalWrite(pinD3, HIGH);
    digitalWrite(pinD4, HIGH);
  }
  else if (digit == 3)
  {
    digitalWrite(pinD1, HIGH); 
    digitalWrite(pinD2, HIGH);
    digitalWrite(pinD3, LOW);
    digitalWrite(pinD4, HIGH);
  }
  else if (digit == 4)
  {
    digitalWrite(pinD1, HIGH); 
    digitalWrite(pinD2, HIGH);
    digitalWrite(pinD3, HIGH);
    digitalWrite(pinD4, LOW);
  }

  

    if (num == 0)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
    }
    else if (num == 1)
    {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
    }
    else if (num == 2)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
    }
    else if (num == 3)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
    }
    else if (num == 4)
    {
      digitalWrite(pinA, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinD, LOW);
    }
    else if (num == 5)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinE, LOW);
    }
    else if (num == 6)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinB, LOW);
    }
    else if (num == 7)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
    }
    else if (num == 8)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
    }
    else if (num == 9)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
    }
    digitalWrite(pinDecimal,HIGH);
  }
