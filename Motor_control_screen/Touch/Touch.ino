#define Y1 A2  // must be an analog pin, use "An" notation!
#define X2 A3  // must be an analog pin, use "An" notation!
#define Y2 8   // can be a digital pin
#define X1 7

int Xme();
int Yme();
int pressureMe();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  //int x, y, pressure;

  if (pressureMe()>10)
  {
    Serial.print(" "); Serial.print(Xme());
    Serial.print("\t "); Serial.print(Yme());
    Serial.print("\tPressure = "); Serial.println(pressureMe());
  }

  

  delay(100);

}

int Xme()
{
  int x;
  pinMode(X1, OUTPUT);
  pinMode(X2, OUTPUT);

  pinMode(Y1, INPUT);
  pinMode(Y2, INPUT);

  digitalWrite(X1, HIGH);
  digitalWrite(X2, LOW);

  x = analogRead(Y1);

  return (x);
}

int Yme()
{
  int y;
  pinMode(Y1, OUTPUT);
  pinMode(Y2, OUTPUT);

  pinMode(X1, INPUT);
  pinMode(X2, INPUT);

  digitalWrite(Y1, HIGH);
  digitalWrite(Y2, LOW);

  y = analogRead(X1);

  return (y);
}

int pressureMe()
{

  pinMode(X1, OUTPUT);
  pinMode(X2, INPUT);

  pinMode(Y1, INPUT);
  pinMode(Y2, OUTPUT);

  digitalWrite(X1, LOW);
  digitalWrite(X2, LOW);

  digitalWrite(Y1, LOW);
  digitalWrite(Y2, HIGH);

  int z1 = analogRead(X2);
  int z2 = analogRead(Y1);

  return (1023-(z2-z1)); 
}
