int pbIn = 2;
volatile int state = LOW;
volatile int current_state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pbIn , INPUT);
  attachInterrupt(0, stateChange, CHANGE);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  /*for(int i = 0; i < 100; i++)
  {
    delay(10);
  }*/
  digitalWrite(LED_BUILTIN, state);
}
void stateChange()
{
  if (state == LOW)
  {
    state = HIGH;
  }
  else
  {
    state = LOW;
  }
  //current_state != current_state;
  digitalWrite(LED_BUILTIN, state);
  Serial.print(state);
}
