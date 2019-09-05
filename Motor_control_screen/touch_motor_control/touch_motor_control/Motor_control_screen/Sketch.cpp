/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//#include <stdint.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
//#include "Adafruit_TFTLCD.h"
#include "TouchScreen.h"
#include <Servo.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void chooseMotor(void );
void stepper_control(void );
//End of Auto generated function prototypes by Atmel Studio
//#include "home"


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

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Servo myservo;


char motor = 'O'; 
bool turkeyTimeBomb = true;

void main_menu(void);
void servo_control(void);
void Stepper_control(void);
void num_pad(void);
int read_numPad(void);

void setup() {
  Serial.begin(9600);
  tft.begin();
  myservo.attach(9);
  myservo.write(0);
  tft.fillScreen(WHITE);
  tft.setRotation(1);
  main_menu();
 // chooseMotor();
  /*if (motor == 'S')
  {
    servo_control();
  }*/

}

void loop() 
{
  /*chooseMotor();
  if (motor == 'S')
  {
    servo_control();
  }*/
  
    //Serial.println(digitChar);
    //delay(2000);
  
  
}

void main_menu(void)
{
  tft.setCursor(85,5);
  tft.setTextColor(BLUE); 
  tft.setTextSize(3); 
  tft.setTextWrap(true);

  tft.println("Main Menu:\n");
  tft.setTextSize(1);
  tft.setCursor(95,35);
  tft.println("Choose motor to control.");

  tft.drawCircle(85,115,40,BLUE);
  //tft.fillCircle(85,115,40,BLUE);
  tft.setTextColor(BLUE); 
  //tft.drawRect(60,100, 50, 40, BLUE);
  tft.setCursor(70, 110);
  tft.print("Servo");

  tft.drawCircle(255, 115, 40, BLUE);
  //tft.fillCircle(255, 115, 40, BLUE);
 // tft.drawRect(230, 100, 50, 40, BLUE);
  tft.setCursor(235, 110);
  tft.print("Stepper");

  while(turkeyTimeBomb == true)
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

  if (p.z > ts.pressureThreshhold)
  {
    if ((p.x >= 477 && p.x <= 667)&&(p.y >= 226 && p.y <= 350))
      motor = 'S';
    else if ((p.x >= 467 && p.x <= 641)&&(p.y >= 678 && p.y <= 788))
      motor = 'T';
  }
    delay(100);
}

void servo_control(void)
{
  tft.fillScreen(WHITE);
  tft.setCursor(45,5);
  tft.setTextColor(BLUE); 
  tft.setTextSize(3); 
  tft.println("Servo Control");
  num_pad();
  int servo_pos = read_numPad();
  
  if (servo_pos >= 0 && servo_pos <=180)
    myservo.write(servo_pos);
  else
  {
    tft.fillRect(54,119,214,49,BLACK);
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
  tft.setCursor(30,5);
  tft.setTextColor(BLUE); 
  tft.setTextSize(3); 
  tft.println("Stepper Control");
  num_pad();
  int stepper_pos = read_numPad();
  Serial.println(stepper_pos);
  stepper_control();
}

void num_pad(void)
{
  tft.drawFastVLine(107, 45, 200, BLUE);
  tft.drawFastVLine(214, 45, 200, BLUE);

  tft.drawFastHLine(0, 94, 320, BLUE);
  tft.drawFastHLine(0, 143, 320, BLUE);
  tft.drawFastHLine(0, 191, 320, BLUE);

  tft.fillRect(214, 191, 320, 240, BLUE);
  
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

  tft.setCursor(267,217);
  
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
  int16_t x, y;
  char c = 'z';
  int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0, count0 = 0;
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0, c0 = 0;
  
  while (turkeyTimeBomb == true)
  {
    //pushed = false;
   // c = 'p';
    TSPoint p = ts.getPoint();

    if (p.z > 0)
    {
        pushed = true;
       if ((p.x >= 668 && p.x <= 766)&&(p.y >= 143 && p.y <= 275))
       {
          digitChar = '1';
          x = p.x;
           pushed = true;
           c = 't';
           count1++;
       }
          
       else if ((p.x >= 687 && p.x <= 767)&&(p.y >= 421 && p.y <= 559))
       {
          digitChar = '2';
          x = p.x;
           pushed = true;
           c ='t';
           count2++;
       }
     
       else if ((p.x >= 687 && p.x <= 772)&&(p.y >= 699 && p.y <= 823))
       {
          digitChar = '3';
           x = p.x;
            pushed = true;
            c = 't';
            count3++;
       }
         
       else if ((p.x >= 517 && p.x <= 571)&&(p.y >= 147 && p.y <= 305))
       {
          digitChar = '4';
          x = p.x;
           pushed = true;
           c = 't';
           count4++;
       }
          
       else if ((p.x >= 513 && p.x <= 563)&&(p.y >= 396 && p.y <= 586))
       {
          digitChar = '5';
          x = p.x;
           pushed = true;
           c = 't';
           count5++;
       }
          
       else if ((p.x >= 514 && p.x <= 560)&&(p.y >= 698 && p.y <= 874))
       {
          digitChar = '6';
          x = p.x;
           pushed = true;
           c = 't';
           count6++;
       }
          
       else if ((p.x >= 333 && p.x <= 400)&&(p.y >= 144 && p.y <= 307))
       {
          digitChar = '7';
          x = p.x;
           pushed = true;
           c = 't';
           count7++;
       }
      
       else if ((p.x >= 335 && p.x <= 384)&&(p.y >= 405 && p.y <= 587))
       {
          digitChar = '8';
          x = p.x;
           pushed = true;
           c = 't';
           count8++;
       }
          
       else if ((p.x >= 353 && p.x <= 400)&&(p.y >= 686 && p.y <= 851))
       {
           digitChar = '9';
           x = p.x;
            pushed = true;
            c = 't';
            count9++;
       }
         
       else if ((p.x >= 191 && p.x <= 230)&&(p.y >= 416 && p.y <= 593))
       {
          digitChar = '0';
          x = p.x;
           pushed = true;
           c = 't';
           count0++;
       }
          
       else if ((p.x >= 179 && p.x <= 217)&&(p.y >= 701 && p.y <= 869))
          turkeyTimeBomb = false;
    }

    

   if (digitChar != Char || (c0 < count0 || c1 < count1 || c2 < count2 || c3 < count3 || c4 < count4 || c5 < count5 || c6 < count6 || c7 < count7 || c8 < count8 || c9 < count9))
    {
      tft.setCursor(54, 217);
      posString += digitChar;
      pos = posString.toInt();
      tft.setTextColor(BLUE);
      if (countDigit!=0)
        tft.print(pos);
     // Serial.println(pos);
      point = x;
      Char = digitChar;
      countDigit++;
      pushed = false;
      c0 = count0; c1 = count1; c2 = count2; c3 = count3; c4 = count4; c5 = count5; c6 = count6; c7 = count7; c8 = count8; c9 = count9; 
    }
    /*else if (digitChar == Char && (c0 < count0 || c1 < count1 || c2 < count2 || c3 < count3 || c4 < count4 || c5 < count5 || c6 < count6 || c7 < count7 || c8 < count8 || c9 < count9))
    {
      tft.setCursor(54, 217);
      posString += digitChar;
      pos = posString.toInt();
      tft.setTextColor(BLUE);
      if (countDigit!=0)
        tft.print(pos);
      Char = digitChar;
      c0 = count0; c1 = count1; c2 = count2; c3 = count3; c4 = count4; c5 = count5; c6 = count6; c7 = count7; c8 = count8; c9 = count9;
    }*/

    delay(200);
    /*else if (digitChar == Char)
    {
      if (pushed)
      {
         tft.setCursor(54, 217);
         posString += digitChar;
         pos = posString.toInt();
      tft.setTextColor(BLUE);
      if (countDigit!=0)
        tft.print(pos);
     // Serial.println(pos);
      point = p.x;
      Char = digitChar;
      countDigit++;
      pushed = false;
      }*/
    }
   /* else if (digitChar == Char && pushed == true && turkeyTimeBomb != false)
    {
      tft.setCursor(54, 217);
      posString += digitChar;
      pos = posString.toInt();
      tft.setTextColor(BLUE);
      if (pos != 0 && countDigit > 0)
        tft.print(pos);
     // Serial.println(pos);
      point = p.x;
      Char = digitChar;
      countDigit++;
      pushed = false;
    }*/

    //delay(100);
  //}

 // Serial.println("Ok!");
  tft.fillRect(50,200,50,30, WHITE);

  return pos;
   
}


