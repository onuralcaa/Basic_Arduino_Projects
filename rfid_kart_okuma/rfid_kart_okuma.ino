#include <SPI.h>   
#include <RFID.h>  
RFID rfid(10,9);
#include<Servo.h>
Servo servo1;
int seviye;
       
void setup() {
  pinMode(A1 , INPUT);
  servo1.attach(2);
  Serial.begin(9600);
  servo1.write(0); 
  SPI.begin();         
  rfid.init();         
}
 
void loop() {
  int sayac;
   seviye = analogRead(A1);
  if(rfid.isCard()&&(seviye >= 400))      
  {
    servo1.write(90);
    for(sayac=0 ; sayac <=110 ; sayac++)
    {
      Serial.println(seviye);
      Serial.println(sayac);
      delay(1000);
    }
    if(sayac == 111)
    {
      rfid.halt();
      servo1.write(0);
    }  
//    if(rfid.readCardSerial()  )   
//    {    
////      Serial.print("Kart ID: ");
////      Serial.print(rfid.serNum[0],HEX);   
////      Serial.print(rfid.serNum[1],HEX);  
////      Serial.print(rfid.serNum[2],HEX);
////      Serial.print(rfid.serNum[3],HEX);
////      Serial.println(rfid.serNum[4],HEX);
//       
//    }
  }
//  else
//  { 
//    rfid.halt();
//    servo1.write(0);
//  }
}
