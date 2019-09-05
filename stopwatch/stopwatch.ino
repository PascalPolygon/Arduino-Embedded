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

void disp(int num, int digit);

void turnOff(void);

void setup() {
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:
 /* digitalWrite(pinD1, LOW);
  digitalWrite(pinD2, HIGH);
  digitalWrite(pinD3, HIGH);
  digitalWrite(pinD4, HIGH);

  // Display zero on digit one

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  digitalWrite(pinDecimal, HIGH);
  
  delay(1000);

  digitalWrite(pinD1, HIGH);
  digitalWrite(pinD2, HIGH);
  digitalWrite(pinD3, HIGH);
  digitalWrite(pinD4, HIGH);

  // Display zero on digit one

 /* digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinDecimal, HIGH);*/
  //delay(1000);

  disp(0,1);
  disp(0,2);
  disp(0,3);
  disp(0,4);

}

void disp(int num, int digit)
{

 // turnOff();
  if (digit == 1)
    digitalWrite(pinD1, LOW); 
  else if (digit == 2)
    digitalWrite(pinD2, LOW);
  else if (digit == 3)
    digitalWrite(pinD3, LOW);
  else if (digit == 4)
    digitalWrite(pinD4, LOW);
  

    if (num == 0)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
    }
    else if (num == 1)
    {
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
    }
    else if (num == 2)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
    }
    else if (num == 3)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinC, HIGH);
    }
    else if (num == 4)
    {
      digitalWrite(pinF, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinC, HIGH);
    }
    else if (num == 5)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinC, HIGH);
    }
    else if (num == 6)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinE, HIGH);
    }
    else if (num == 7)
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
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
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
    }
  }


void turnOff(void)
{
  digitalWrite(pinD1, HIGH);
  digitalWrite(pinD2, HIGH);
  digitalWrite(pinD3, HIGH);
  digitalWrite(pinD4, HIGH);
  
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
