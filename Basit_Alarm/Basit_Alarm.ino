int PIRpin = 8;  // PIR sensörün bağlı olduğu data pini
int deger = 2;
int durum;
int zaman;
int sayac=0;
//2150 = 5 dk
void setup() {
  pinMode(PIRpin,INPUT); 
  pinMode(deger, OUTPUT); 
  Serial.begin(57600);  // Seri portu başlat
  delay(30000);
}
void loop() {
  zaman = millis();
  //Serial.println(digitalRead(PIRpin));  // PIR sensörden okunan veriyi seri port ekranına yaz
  //delay(5);  // Yarım saniye bekle

    durum = digitalRead(PIRpin);
  
     if(durum == 1) sayac++;

     if(sayac == 4)
     {
      for(int i=0 ; i<2000 ; i++)
      {
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        delay(75);
      }
      sayac=0;
     }

    if(zaman % 30000 == 0)
    {
      digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
      delay(50);
      digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
      delay(50);
    }

     

     Serial.println(zaman);

     
  
    
    



}
