
int i;
void setup() {

 pinMode(3, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT); 
 pinMode(9, OUTPUT);
 Serial.begin(9600);

}

void loop() {

 for(i=0 ; i<=170 ; i=i+5)
 {
  analogWrite(3, i);
  analogWrite(5, i);
  analogWrite(6, i);  
  analogWrite(9, i);
  delay(100);
  Serial.println(i);
 }
delay(3000);
 


 
}
