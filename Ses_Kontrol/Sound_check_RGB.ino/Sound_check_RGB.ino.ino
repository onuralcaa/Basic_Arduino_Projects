
int led=12; 

int sensorpin = 7;
int durum; 

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
 
  }
  
  else{
    digitalWrite(led, HIGH);
    durum++;
    }


    
Serial.println(durum); 
}
