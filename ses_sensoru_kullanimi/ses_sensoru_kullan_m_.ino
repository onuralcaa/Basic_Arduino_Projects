void setup() {
  pinMode(2,INPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
}
void loop() {
  
  if (digitalRead(2)==HIGH) 
    Serial.print("Gürültü eşik değer üstünde...");
  
  else 
  {
    Serial.print("Gürültü eşik değer altında...");
  }
  
  
  int deger = analogRead(A0);  
  Serial.println(deger);   
  }
