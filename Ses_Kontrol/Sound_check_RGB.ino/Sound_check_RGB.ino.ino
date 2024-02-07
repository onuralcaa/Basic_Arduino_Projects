
int led=12; 

int sensorpin = 7;
int durum=1; 

void setup() 
{
  
pinMode(led,OUTPUT); 
pinMode(sensorpin,INPUT); 

Serial.begin(9600); 

}

void loop() 
{
  
  
if (digitalRead(sensorpin) == HIGH) { 

  
  digitalWrite(led, LOW);
  delay(1);
 
  }
  
  else{
    digitalWrite(led, HIGH);
    durum++;
    if(durum >= 6) durum = 0;
    delay(1);
    }


    
Serial.println(durum); 
}
