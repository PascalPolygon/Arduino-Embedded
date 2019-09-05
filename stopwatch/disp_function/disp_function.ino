void disp(int num, int digit)
{

  turnOff();
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
