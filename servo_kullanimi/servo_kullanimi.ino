#include<Servo.h>
Servo servo1;
int seviye;

void setup() {
 pinMode(A1 , INPUT);
 servo1.attach(2);
 Serial.begin(9600);
 servo1.write(0);
}
 
void loop(){
  seviye = analogRead(A1);
  Serial.println(seviye);

  if(seviye <= 200)
  {
    servo1.write(90);
  }
  else
  {
    servo1.write(0);
  }
 

}
