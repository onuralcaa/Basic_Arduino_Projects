#include <Servo.h>

Servo Servo1;

//Left side motor
const int EnL = 5;
const int HighL = 6;
const int LowL = 7;

//Right side motor
const int EnR = 3;
const int HighR = 2;
const int LowR = 4;


void setup() {

  Servo1.attach(9);

  pinMode(EnL, OUTPUT);
  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);

  pinMode(EnR, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);

}

void Forward()
{
  //Right motor
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, 150);

  //Left motor
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, 150);
}

void Backward()
{
  //Right motor
  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnR, 150);

  //Left motor
  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnL, 150);
}


void loop()
{
  //Forward();
  //Backward();

  /*
     MAX RIGHT 45
     MAX LEFT 145
  */

/*
  for (int i = 45; i <= 145 ; i++)
  {
    Servo1.write(i);
    delay(100);
    if (i == 145) i = 0;
  }
*/

}
