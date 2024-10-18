#include <Servo.h>

Servo Servo1;

//Left side motor
const int EnA = 5;
const int HighL = 6;
const int LowL = 7;

//Right side motor
const int EnB = 10;
const int HighR = 8;
const int LowR = 9;


void setup() {
  
  Servo1.attach(3);
    
  pinMode(EnB, OUTPUT);
  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);

  pinMode(EnB, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);
}

void Forward()
{
  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnA, 75);

  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnB, 75
  );

}
void loop() {
  //Forward();

  Servo1.write(95);

}
