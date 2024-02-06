// C++ code
//
int sw1 = 10;
int sw2 = 11;

int durum1;
int durum2;

void setup()
{
  Serial.begin(9600);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  
  
   
}

void loop()
{
 
  durum1 = digitalRead(sw1);
  durum2 = digitalRead(sw2);  
 

  Serial.print(durum1);
  Serial.println(durum2);
  delay(100);
  
  
}
