/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>
#include <Adafruit_ILI9341.h>
#include <TouchScreen.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void main_menu_display();
void main_menu_read();
void enter_mode_1();
void enter_mode_2();
void mode_2_read();
void enter_mode_3();
void mode_3_read();
//End of Auto generated function prototypes by Atmel Studio



//Touchscreen X+ X- Y+ Y- pins
#define YP A1//A2  // must be an analog pin, use "An" notation!
#define XM A0//A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 7   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define BLACK   0x0000 
#define BLUE    0x001F 
#define RED     0xF800 
#define GREEN   0x07E0 
#define CYAN    0x07FF 
#define MAGENTA 0xF81F 
#define YELLOW  0xFFE0 
#define WHITE   0xFFFF

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Screen setup*************************************************************************************************
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

boolean RecordOn = false;

#define INSPACE 20
#define OUTSPACE 20
#define mm_FRAME_X 100
#define mm_FRAME_Y 90
#define mm_FRAME_W 80
#define mm_FRAME_H 80
#define mm_CursXoff1 5
#define mm_CursYoff1 18
#define mm_CursXoff2_1 8
#define mm_CursXoff2_2 11
#define mm_CursXoff2_3 2
#define mm_CursYoff2 -10
#define mm_CursXoff3 65
#define mm_CursYoff3 30
int mm_FRAME_X1=OUTSPACE;
int mm_FRAME_X2=OUTSPACE+mm_FRAME_W+INSPACE;
int mm_FRAME_X3=OUTSPACE+mm_FRAME_W*2+INSPACE*2;

#define M1_CursXoff1 53
#define M1_CursYoff1 30
#define M1_CursXoff2 35
#define M1_CursYoff2 55
#define M1_CursXoff3 140
#define M1_CursYoff3 160
#define M1_FRAME_X 42
#define M1_FRAME_Y 119
#define M1_FRAME_W 242
#define M1_FRAME_H 22
#define M1_DEL_X 140
#define M1_DEL_Y 160
#define M1_DEL_W 8
#define M1_DEL_H 8
int M1_BAR_X=M1_FRAME_X+1;
int M1_BAR_Y=M1_FRAME_Y+1;
int M1_BAR_W=(M1_FRAME_W-2)/10;
int M1_BAR_H=M1_FRAME_H-2;

#define M2_CursXoff1 55
#define M2_CursYoff1 30
#define M2_CursXoff2 62
#define M2_CursYoff2 55
#define M2_CursXoff3_1 27
#define M2_CursXoff3_2 5
#define M2_CursYoff3_1 10
#define M2_CursYoff3_2 -4
#define M2_CursXoff4_1 102
#define M2_CursXoff4_2 100
#define M2_CursYoff4 108
#define M2_FRAME_W 123
#define M2_FRAME_H 40
#define M2_DEL_W 92
#define M2_DEL_H 25
int M2_FRAME_X=(320-M2_FRAME_W)/2;
int M2_FRAME_Y=((240-M2_FRAME_H)/2)+70;

#define M3_CursXoff1 38
#define M3_CursYoff1 30
#define M3_CursXoff2 73
#define M3_CursYoff2 55
#define M3_CursXoff3_1 27
#define M3_CursXoff3_2 5
#define M3_CursYoff3_1 10
#define M3_CursYoff3_2 3
#define M3_FRAME_W 123
#define M3_FRAME_H 30
int M3_FRAME_X=(320-M3_FRAME_W)/2;
int M3_FRAME_Y=((240-M3_FRAME_H)/2)+10;

int V_min=0;
int V_max=5;
int A_min=2;
int A_max=1018;

// SD card chip select **********************************************************************************
#define CCS 4

//Pot setup
int sensorPin = A2;  
int sensorValue = 0;
int logging = 0;
float voltage = 0;

//acc setup
bool sendData = false;
Adafruit_LSM303 lsm;

//Create and open text file
//File dataFile = SD.open("datalog.txt", FILE_WRITE);

bool dataLogger = true;

//void main_menu_display(void);

/*ISR(TIMER1_COMPA_vect)
{ 
  if (logging < 400)
  {
    sendData = true;
    logging ++;
  }
  else if (logging == 400)
    dataLogger = false;
}*/
  

void setup() {
  

  
// Init SD card ****************************************************************************************************
    
  Serial.begin(57600);
  while (!Serial)
  {
    ;
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(CCS)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
 // delay(20);

  // Init Accelerometer******************************************************************************

  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
    //Serial.begin(9600);
  
    // Try to initialise and warn if we couldn't detect the chip
    if (!lsm.begin())
    {
      Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
      while (1);
    }
  
  Serial.println("Channel 1 (Potentiometer)    Channel 2 (Digital compass(I2C))");
  
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println("Channel 1 (Potentiometer)    Channel 2 (Digital compass(I2C))");
    dataFile.close();
  }
  else
  {
    Serial.println("Error opening file in setup:("); dataFile.println("Error opening file :("); 
  }

   tft.begin();
   tft.setRotation(1);

 // delay(10);

  main_menu_display();
  
// Init timer interupt  *************************************************************************
  /*cli(); //top interrupts
  //set timer1 interrupt at 1KHz
  TCCR1A &= ~(1 << WGM10);
  TCCR1B &= ~(1 << CS10);
  TCCR1A = 0;// Timer/Counter Control Registers set TCCR1A register=0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//Timer/Counter initialize counter value to 0
  OCR1A = 49999;// Compare Registers = (16*10^6) / (40*8) - 1, set timer count for 40hz increments

  TCCR1B |= (1 << WGM12);   // turn on CTC mode
  TCCR1B |= (1 << CS11); // Set CS11 bit for 8 prescaler
  TIMSK1 |= (1 << OCIE1A); //Timer interrupt Mask
  sei();*///allow interrupts

// init tft screen *********************************************************************************************

 /* tft.begin();
  tft.setRotation(1);*/
  //main_menu_display();

}

/*void init_timer(void)
{
  cli(); //top interrupts
  //set timer1 interrupt at 1KHz
  TCCR1A &= ~(1 << WGM10);
  TCCR1B &= ~(1 << CS10);
  TCCR1A = 0;// Timer/Counter Control Registers set TCCR1A register=0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//Timer/Counter initialize counter value to 0
  OCR1A = 49999;// Compare Registers = (16*10^6) / (40*8) - 1, set timer count for 40hz increments

  TCCR1B |= (1 << WGM12);   // turn on CTC mode
  TCCR1B |= (1 << CS11); // Set CS11 bit for 8 prescaler
  TIMSK1 |= (1 << OCIE1A); //Timer interrupt Mask
  sei();//allow interrupts
}*/

void loop() 
{

 // Serial.println("Inside loop");
  if (dataLogger)
  {
   if (sendData)
   {
    lsm.read();
    File dataFile = SD.open("datalog.csv", FILE_WRITE);

    if (dataFile)
    {
      // Print Potentiometer values******************************************************************************************************

      sensorValue = analogRead(sensorPin);
      voltage = sensorValue * 5.0/ 1023.0;
      Serial.print("       "); Serial.print(voltage, 3);Serial.print(",");
      dataFile.print("       "); dataFile.print(voltage);dataFile.print(",");

       // Print Accelerometer values***************************************************************************************************************
       
       Serial.print("               ");Serial.print((int)lsm.accelData.x);Serial.print(",");
       Serial.print((int)lsm.accelData.y); Serial.print(",");
       Serial.println((int)lsm.accelData.z);

      dataFile.print("               ");dataFile.print((int)lsm.accelData.x);dataFile.print(",");
      dataFile.print((int)lsm.accelData.y);dataFile.print(",");
      dataFile.println((int)lsm.accelData.z);
      dataFile.close();
      
      sendData = false;
    }
    else 
      Serial.println("Error opening file in loop:("); dataFile.println("Error opening file :(");

    if (logging >= 400)
      dataFile.close();
  
  }
 
}
}


void main_menu_display()
{

 
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(mm_FRAME_X1+mm_CursXoff1, mm_FRAME_Y+(mm_FRAME_H/2)-mm_CursYoff1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("MODE 1");
  tft.setCursor(mm_FRAME_X2+mm_CursXoff1, mm_FRAME_Y+(mm_FRAME_H/2)-mm_CursYoff1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("MODE 2");
  tft.setCursor(mm_FRAME_X3+mm_CursXoff1, mm_FRAME_Y+(mm_FRAME_H/2)-mm_CursYoff1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("MODE 3");
  tft.setCursor(mm_FRAME_X1+mm_CursXoff2_1, mm_FRAME_Y+(mm_FRAME_H/2)-mm_CursYoff2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Data Logger");  
  tft.setCursor(mm_FRAME_X2+mm_CursXoff2_2, mm_FRAME_Y+(mm_FRAME_H/2)-mm_CursYoff2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Volt Meter");  
  tft.setCursor(mm_FRAME_X3+mm_CursXoff2_3, mm_FRAME_Y+(mm_FRAME_H/2)-mm_CursYoff2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Data Retrieve");
  tft.setCursor(mm_CursXoff3, mm_CursYoff3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("Select Mode");
  tft.drawRect(mm_FRAME_X1, mm_FRAME_Y, mm_FRAME_W, mm_FRAME_H, ILI9341_WHITE);
  tft.drawRect(mm_FRAME_X2, mm_FRAME_Y, mm_FRAME_W, mm_FRAME_H, ILI9341_WHITE);
  tft.drawRect(mm_FRAME_X3, mm_FRAME_Y, mm_FRAME_W, mm_FRAME_H, ILI9341_WHITE);
  main_menu_read();
}

void main_menu_read()
{
  while (0<1){
   // Retrieve a point  
  TSPoint p = ts.getPoint();

  // See if there's any  touch data for us
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {   
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    int x = p.y;
    
    if((x > mm_FRAME_X1) && (x < (mm_FRAME_X1 + mm_FRAME_W))) {
      if ((y > mm_FRAME_Y) && (y <= (mm_FRAME_Y + mm_FRAME_H))) {
        Serial.println("Mode 1 Selected"); 
        enter_mode_1();
      }
    }
    else if((x > mm_FRAME_X2) && (x < (mm_FRAME_X2 + mm_FRAME_W))) {
      if ((y > mm_FRAME_Y) && (y <= (mm_FRAME_Y + mm_FRAME_H))) {
        Serial.println("Mode 2 Selected"); 
        enter_mode_2();
      }
    }
    else if((x > mm_FRAME_X3) && (x < (mm_FRAME_X3 + mm_FRAME_W))) {
      if ((y > mm_FRAME_Y) && (y <= (mm_FRAME_Y + mm_FRAME_H))) {
        Serial.println("Mode 3 Selected"); 
        enter_mode_3();
      }
    }
    Serial.println(RecordOn);
  }
  }
} 

void enter_mode_1()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(M1_CursXoff1,M1_CursYoff1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("MODE 1: Data Logger");
  tft.setCursor(M1_CursXoff2,M1_CursYoff2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Reading Accelerometer & Magnetometer Data...");
  
  
  main_menu_display();
}

void enter_mode_2()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(M2_CursXoff1,M2_CursYoff1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("MODE 2: Volt Meter");
  tft.setCursor(M2_CursXoff2,M2_CursYoff2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Real-time Volt Meter Measurements:");
  tft.setCursor(M2_CursXoff4_1+M2_CursXoff4_2,M2_CursYoff4);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("V");
  tft.drawRect(M2_FRAME_X, M2_FRAME_Y, M2_FRAME_W, M2_FRAME_H, ILI9341_WHITE);
  tft.setCursor(M2_FRAME_X+M2_CursXoff3_1, M2_FRAME_Y+(M2_FRAME_H/2)-M2_CursYoff3_1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Complete and");
  tft.setCursor(M2_FRAME_X+M2_CursXoff3_2, M2_FRAME_Y+(M2_FRAME_H/2)-M2_CursYoff3_2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Return to Main Menu");  

  mode_2_read();
}

void mode_2_read()
{
  while (0<1){
   // Retrieve a point  
  TSPoint p = ts.getPoint();

  // See if there's any  touch data for us
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {   
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    int x = p.y;
    
    if((x > M2_FRAME_X) && (x < (M2_FRAME_X + M2_FRAME_W))) {
      if ((y > M2_FRAME_Y) && (y <= (M2_FRAME_Y + M2_FRAME_H))) {
        //Serial.println("Returned to Main Menu (from Mode 2)"); 
        main_menu_display();
      }
    }
    //Serial.println(RecordOn);
  }
  float Pot_Val=analogRead(2);
  float Pot_Volt=(Pot_Val - A_min)*(V_max-V_min)/(A_max-A_min);
  //Serial.println(Pot_Volt,3);
  tft.fillRect(M2_CursXoff4_1,M2_CursYoff4,M2_DEL_W,M2_DEL_H,ILI9341_BLACK);
  tft.setCursor(M2_CursXoff4_1,M2_CursYoff4);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println(Pot_Volt,3);
  delay(50); 
  }
} 

void enter_mode_3()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(M3_CursXoff1,M3_CursYoff1);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println("MODE 3: Data Retrieve");
  tft.setCursor(M3_CursXoff2,M3_CursYoff2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Sending Data to PC Text File...");
  tft.drawRect(M3_FRAME_X, M3_FRAME_Y, M3_FRAME_W, M3_FRAME_H, ILI9341_WHITE);
  tft.setCursor(M3_FRAME_X+M3_CursXoff3_2, M3_FRAME_Y+(M3_FRAME_H/2)-M3_CursYoff3_2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("Return to Main Menu");  

  mode_3_read();
}

void mode_3_read()
{
  while (0<1){
   // Retrieve a point  
  TSPoint p = ts.getPoint();

  // See if there's any  touch data for us
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {   
    // Scale using the calibration #'s
    // and rotate coordinate system
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    int y = tft.height() - p.x;
    int x = p.y;
    
    if((x > M3_FRAME_X) && (x < (M3_FRAME_X + M3_FRAME_W))) {
      if ((y > M3_FRAME_Y) && (y <= (M3_FRAME_Y + M3_FRAME_H))) {
        Serial.println("Returned to Main Menu (from Mode 3)"); 
        main_menu_display();
      }
    }
    Serial.println(RecordOn);
  }
  }
} 
