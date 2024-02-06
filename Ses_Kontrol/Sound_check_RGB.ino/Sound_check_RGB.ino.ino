
int led=12; 

int sensorpin = 7;
bool durum; 

void setup() 
{
  
pinMode(led,OUTPUT); 
pinMode(sensorpin,INPUT); 
Serial.begin(9600); 

}

void loop() 
{
  

if (digitalRead(sensorpin) == HIGH) { 
  
  durum = 0; 
  }
  
  else{
    durum = 1;
    }

delay(200);
    
Serial.println(durum); 
}
