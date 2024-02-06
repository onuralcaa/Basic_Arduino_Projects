// C++ code
//
int sensor = A0;
int led = 13;
int durum;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
 
  durum = analogRead(sensor);

  
 
 

  Serial.println(durum);
  
  delay(100);
  
  
}
