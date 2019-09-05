//#include <Serial.h>

int pbIn = 2;
volatile int state = LOW;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pbIn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pbIn), stateChange, RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*for(int i = 0; i < 100; i++)
  {
    delay(10);
  }*/
  if (state == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
  }
  else
    digitalWrite(LED_BUILTIN,LOW);
     
}

void stateChange()
{
  state =! state;
  //state = digitalRead(pbIn);
  //digitalWrite(LED_BUILTIN, state);
  Serial.print(state);

}
