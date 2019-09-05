/*Begining of Auto generated code by Atmel studi
#include <Arduino.h>


/*End of auto generated code by Atmel studio */


//#include <stdint.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "TouchScreen.h"
//Beginning of Auto generated function prototypes by Atmel Studio
void chooseMotor(void);
void stepper_control(void);
//End of Auto generated function prototypes by Atmel Studio

#define F_CPU 16000000


#define BLACK   0x0000 
#define BLUE    0x001F 
#define RED     0xF800 
#define GREEN   0x07E0 
#define CYAN    0x07FF 
#define MAGENTA 0xF81F 
#define YELLOW  0xFFE0 
#define WHITE   0xFFFF


#define TFT_DC 5
#define TFT_CS 10


#define YP A2
#define XM A3  
#define YM 8   
#define XP 7

#define PULSE_MAX 4800
#define PULSE_MIN 1100
#define PULSE_MID 2950

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);



int StepPin = 3;
int DirPin = 2;
int MS1 = 4;
int Steps;
int StopDelay = 1000 * 2;


char motor = 'O';
bool turkeyTimeBomb = true;
int dir;


void main_menu(void);
void servo_control(void);
void stepper_control(void);
void num_pad(void);
int read_numPad(void);


void setup() {

  TCCR1A &= ~(1 << WGM10); //Disable CTC in register 1
  TCCR1A |= (1 << WGM11) | (1 << COM1A1);  //PWM, Phase Correct, 9-bit mode of operation
  TCCR1B |= (1 << WGM12) | (1 << WGM13); //Wave form generation mode
  TCCR1B |= (1 << CS11); //| (1 << CS10);  //prescaler /1 (no prescaler)
  TCCR1B &= ~(1 << CS10); //disable presclaer
  ICR1 = (F_CPU / 50) - 1; //Input capture register (TOP value)

  DDRB |= (1 << PORTB1);

  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  pinMode(MS1, OUTPUT);
  digitalWrite(MS1, HIGH);
  Serial.begin(9600);
  tft.begin();
  OCR1A = PULSE_MID;
  
  tft.fillScreen(WHITE);
  tft.setRotation(1);
  main_menu();

}


void loop()
{

}


void main_menu(void)
{
  tft.setCursor(85, 5);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.setTextWrap(true);


  tft.println("Main Menu:\n");
  tft.setTextSize(1);
  tft.setCursor(95, 35);
  tft.println("Choose motor to control.");


  tft.drawCircle(85, 115, 40, BLUE);
  tft.setTextColor(BLUE);
  tft.setCursor(70, 110);
  tft.print("Servo");


  tft.drawCircle(255, 115, 40, BLUE);
  tft.setCursor(235, 110);
  tft.print("Stepper");


  while (turkeyTimeBomb == true)
  {
    chooseMotor();
    if (motor == 'S' || motor == 'T')
      turkeyTimeBomb = false;
    else
      turkeyTimeBomb = true;
  }
  if (motor == 'S')
    servo_control();
  else if (motor == 'T')
    stepper_control();

}


void chooseMotor(void)
{
  TSPoint p = ts.getPoint();


  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    if ((p.x >= 477 && p.x <= 667) && (p.y >= 226 && p.y <= 350))
      motor = 'S';
    else if ((p.x >= 467 && p.x <= 641) && (p.y >= 678 && p.y <= 788))
      motor = 'T';
  }
  delay(100);
}


void servo_control(void)
{
  tft.fillScreen(WHITE);
  tft.setCursor(80, 10);
  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.println("Servo Control");
  num_pad();
  int servo_pos = read_numPad();

  if (servo_pos >= 0 && servo_pos <= 90)
  {
    servo_write(servo_pos);
  }
  else
  {
    tft.fillRect(54, 119, 214, 49, BLACK);
    tft.setCursor(100, 144);
    tft.setTextColor(RED);
    tft.println("ERROR: Invalid angle value");
    delay(2500);
    servo_control();
  }

  Serial.println(servo_pos);
  servo_control();
}


void stepper_control(void)
{
  tft.fillScreen(WHITE);
  tft.setCursor(75, 10);
  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.println("Stepper Control");
  num_pad();
  int stepper_pos = read_numPad();
  stepper_write(stepper_pos, dir);
  stepper_control();
}


int stepper_write(int StepAngle, int stepper_dir)
{
  if (stepper_dir == 0) {
    Steps = map(StepAngle, 0, 360, 0, 400);
    int i = 1;
    digitalWrite(DirPin, LOW);
    while (i <= Steps) {
      digitalWrite(StepPin, HIGH);
      delay(3);
      digitalWrite(StepPin, LOW);
      delay(3);
      i++;
    }
    int j = 1;
    delay(StopDelay);
    digitalWrite(DirPin, HIGH);
    while (j <= Steps) {
      digitalWrite(StepPin, HIGH);
      delay(3);
      digitalWrite(StepPin, LOW);
      delay(3);
      j++;
    }
  }
  else {
    Steps = map(StepAngle, 0, 360, 0, 400);
    int i = 1;
    digitalWrite(DirPin, HIGH);
    while (i <= Steps) {
      digitalWrite(StepPin, HIGH);
      delay(3);
      digitalWrite(StepPin, LOW);
      delay(3);
      i++;
    }
    int j = 1;
    delay(StopDelay);
    digitalWrite(DirPin, LOW);
    while (j <= Steps) {
      digitalWrite(StepPin, HIGH);
      delay(3);
      digitalWrite(StepPin, LOW);
      delay(3);
      j++;
    }
  }
}

int servo_write(int pos)
{

  if (dir == 0)
  {
    OCR1A = (PULSE_MID)+(pos * ((PULSE_MAX - PULSE_MID) / (90)));
    delay(3000);
    OCR1A = PULSE_MID;
  }

  else if (dir == 1)
  {
    OCR1A = (PULSE_MAX - ((PULSE_MIN)+(pos * ((PULSE_MID - PULSE_MIN) / (90))))) - 800;
    delay(3000);
    OCR1A = PULSE_MID;
  }


}


void num_pad(void)
{
  tft.drawFastVLine(107, 45, 200, BLUE);
  tft.drawFastVLine(214, 45, 200, BLUE);
  tft.drawFastHLine(0, 94, 320, BLUE);
  tft.drawFastHLine(0, 143, 320, BLUE);
  tft.drawFastHLine(0, 191, 320, BLUE);


  tft.fillRect(214, 191, 320, 240, BLUE);
  tft.drawRect(5, 197, 97, 39, RED);


  tft.drawCircle(25, 25, 20, BLUE);
  tft.setCursor(21, 23);
  tft.setTextColor(BLUE);
  tft.setTextSize(1.5);
  tft.println("CW");


  tft.drawCircle(295, 25, 20, BLUE);
  tft.setCursor(287, 23);
  tft.setTextColor(BLUE);
  tft.setTextSize(1.5);
  tft.println("CCW");


  tft.setTextSize(1);
  tft.setCursor(54, 70);
  tft.print(1);
  tft.setCursor(161, 70);
  tft.print(2);
  tft.setCursor(268, 70);
  tft.print(3);
  tft.setCursor(54, 119);
  tft.print(4);
  tft.setCursor(161, 119);
  tft.print(5);
  tft.setCursor(268, 119);
  tft.print(6);
  tft.setCursor(54, 168);
  tft.print(7);
  tft.setCursor(161, 168);
  tft.print(8);
  tft.setCursor(268, 168);
  tft.print(9);
  tft.setCursor(161, 217);
  tft.print(0);


  tft.setCursor(267, 217);

  tft.setTextColor(WHITE);
  tft.print("OK");


}



int read_numPad(void)
{
  int pos = -1;
  int countDigit = 0;
  char digitChar = ' ';
  char Char = 'p';
  String posString = " ";
  bool pushed = false;
  int point = 0;
  turkeyTimeBomb = true;
  bool skepticalBonobo = true;
  int16_t x, y;
  char c = 'z';
  int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0, count0 = 0;
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0, c0 = 0;


  while (skepticalBonobo)
  {
    TSPoint p = ts.getPoint();

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
      if ((p.x >= 753 && p.x <= 867) && (p.y >= 105 && p.y <= 180))
      {
        dir = 1;

        tft.fillCircle(25, 25, 20, BLUE);
        tft.setCursor(21, 23);
        tft.setTextColor(WHITE);
        tft.setTextSize(1.5);
        tft.println("CW");

        skepticalBonobo = false;
      }
      else if ((p.x >= 753 && p.x <= 867) && (p.y >= 798 && p.y <= 872))
      {
        dir = 0;

        tft.fillCircle(295, 25, 20, BLUE);
        tft.setCursor(287, 23);
        tft.setTextColor(WHITE);
        tft.setTextSize(1.5);
        tft.println("CCW");

        skepticalBonobo = false;
      }

    }
    delay(100);
  }



  while (turkeyTimeBomb == true)
  {
    TSPoint p = ts.getPoint();

    /*p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());*/

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
      pushed = true;
      if ((p.x >= 668 && p.x <= 766) && (p.y >= 143 && p.y <= 275))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '1';
        x = p.x;
        pushed = true;
        c = 't';
        count1++;
      }

      else if ((p.x >= 687 && p.x <= 767) && (p.y >= 421 && p.y <= 559))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '2';
        x = p.x;
        pushed = true;
        c = 't';
        count2++;
      }

      else if ((p.x >= 687 && p.x <= 772) && (p.y >= 699 && p.y <= 823))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '3';
        x = p.x;
        pushed = true;
        c = 't';
        count3++;
      }

      else if ((p.x >= 517 && p.x <= 571) && (p.y >= 147 && p.y <= 305))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '4';
        x = p.x;
        pushed = true;
        c = 't';
        count4++;
      }

      else if ((p.x >= 513 && p.x <= 563) && (p.y >= 396 && p.y <= 586))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '5';
        x = p.x;
        pushed = true;
        c = 't';
        count5++;
      }

      else if ((p.x >= 514 && p.x <= 560) && (p.y >= 698 && p.y <= 874))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '6';
        x = p.x;
        pushed = true;
        c = 't';
        count6++;
      }

      else if ((p.x >= 333 && p.x <= 400) && (p.y >= 144 && p.y <= 307))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '7';
        x = p.x;
        pushed = true;
        c = 't';
        count7++;
      }

      else if ((p.x >= 335 && p.x <= 384) && (p.y >= 405 && p.y <= 587))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '8';
        x = p.x;
        pushed = true;
        c = 't';
        count8++;
      }

      else if ((p.x >= 353 && p.x <= 400) && (p.y >= 686 && p.y <= 851))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '9';
        x = p.x;
        pushed = true;
        c = 't';
        count9++;
      }

      else if ((p.x >= 191 && p.x <= 230) && (p.y >= 416 && p.y <= 593))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        digitChar = '0';
        x = p.x;
        pushed = true;
        c = 't';
        count0++;
      }

      else if ((p.x >= 179 && p.x <= 217) && (p.y >= 701 && p.y <= 869))
      {
        Serial.print("X :");Serial.println( map(p.x, TS_MINX, TS_MAXX, 0, tft.width()));
        turkeyTimeBomb = false;
      }
        
    }

    if (digitChar != Char || (c0 < count0 || c1 < count1 || c2 < count2 || c3 < count3 || c4 < count4 || c5 < count5 || c6 < count6 || c7 < count7 || c8 < count8 || c9 < count9))
    {
      tft.setCursor(54, 217);
      posString += digitChar;
      pos = posString.toInt();
      tft.setTextColor(BLUE);
      if (countDigit != 0)
        tft.print(pos);
      point = x;
      Char = digitChar;
      countDigit++;
      pushed = false;
      c0 = count0; c1 = count1; c2 = count2; c3 = count3; c4 = count4; c5 = count5; c6 = count6; c7 = count7; c8 = count8; c9 = count9;
    }

    delay(100);
  }

  tft.fillRect(50, 200, 50, 30, WHITE);

  return pos;
}
