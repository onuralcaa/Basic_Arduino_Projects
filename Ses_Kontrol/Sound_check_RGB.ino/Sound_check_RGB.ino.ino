// C++ code
//
int sensor = A0;

int durum;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
 
  durum = analogRead,(sensor);
 
 

  Serial.println(durum);
  
  delay(100);
  
  
}
