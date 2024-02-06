
float amper_filtre=0;
void setup() {
 Serial.begin(57600);
 
}
void loop() {
  
  float val=analogRead(A0);
  float amp=val*0.0274;

  amper_filtre = amper_filtre * 0.8 + amp * 0.2;
  
  Serial.println(val);
  delay(300);
}
