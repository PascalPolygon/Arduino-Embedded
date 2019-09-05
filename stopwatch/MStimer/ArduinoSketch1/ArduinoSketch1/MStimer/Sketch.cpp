/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <MsTimer2.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void flash();
//End of Auto generated function prototypes by Atmel Studio



int pinA = 9; // segment 11
int pinB = 8; // segment 7
int pinC = 7; // segment 4
int pinD = 6; // segment 2
int pinE = 5; // segment 1
int pinF = 4; // segment 10
int pinG = 3; // segment 5
int pinDecimal = 2; // D5/D6
   
int pinD1 = 10; // digit 1
int pinD2 = 11; // digit 2
int pinD3 = 12; // digit 3
int pinD4 = 13; // digit 4


void flash() {
  static boolean output = HIGH;

  digitalWrite(D1, LOW)
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  
  digitalWrite(pinA, output);
  digitalWrite(pinB, output);
  digitalWrite(pinC, output);
  digitalWrite(pinD, output);
  digitalWrite(pinE, output);
  digitalWrite(pinF, output);
  digitalWrite(pinG, !output);
  output = !output;
}

void setup() {
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

  MsTimer2::set(500, flash); // 500ms period
  MsTimer2::start();
}

void loop() {
}
