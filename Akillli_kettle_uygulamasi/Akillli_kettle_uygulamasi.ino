#include<Servo.h>
Servo servo1;
int mavi_led =3;
int kirmizi_led =4; 
int buzzer = 5;
int kontrol=0;
unsigned int Sicaklik;
void setup()
{
  servo1.attach(2);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Sicaklik = analogRead(A5);
  Serial.println(Sicaklik);  

    if(Sicaklik <= 220)
  {
    servo1.write(60);
    //digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW); 
  }
  else
  {
    servo1.write(0);
    //digitalWrite(3, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    kontrol=0;

  }   
}
