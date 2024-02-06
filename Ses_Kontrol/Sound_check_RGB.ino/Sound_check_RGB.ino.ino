// C++ code
//
int sensor = 2;

bool durum;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop()
{
 
  durum = digitalRead,(sensor);
 
 

  Serial.println(durum);
  
  delay(100);
  
  
}
