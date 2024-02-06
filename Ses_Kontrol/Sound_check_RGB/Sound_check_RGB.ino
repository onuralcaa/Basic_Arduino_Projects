// C++ code
//
int sw1 = 2;

int durum;
int deger = 0;

int led1 = 10;
int led2 = 11;
int led3 = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(sw1, INPUT);
  
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
}

void loop()
{
  durum = digitalRead(sw1);
  
  if(durum == HIGH)
  {
    deger = 1;
  }
  
   else if(durum == LOW)
  {
    deger = 2;
  }
  
  else 
  {
    deger = 3;
  }
  
 
  Serial.print(deger);
  Serial.println('\n');
  delay(100);
  
  
}
