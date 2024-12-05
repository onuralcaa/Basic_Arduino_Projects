#include <Servo.h>
#include "NewPing.h"

//HCSR04 sensor degiskenleri
#define ECHO_PIN 13
#define TRIGGER_PIN 12
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float duration, distance;


Servo Servo1;

int resultValue = 0; // Gelen değer için değişken

// PID parametreleri
float Kp = 1.25;   // Proportional katsayısı
float Ki = 0.0;    // Integral katsayısı
float Kd = 0.75;   // Derivative katsayısı

float previousError = 0;
float integral = 0;

// Servo sınırları
int servoMin = 50;    // Servo minimum açısı (sağ)
int servoMax = 130;   // Servo maksimum açısı (sol)
int servoCenter = 90; // Servo merkezi (direksiyon sıfır konumu)

// Left motor pins
const int EnL = 5;
const int HighL = 6;
const int LowL = 7;

// Right motor pins
const int EnR = 3;
const int HighR = 2;
const int LowR = 4;

// Zaman kontrolü için değişken
unsigned long startTime;

void setup() {
  Serial.begin(57600); // Seri haberleşmeyi başlat

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Servo motoru pin 9'a bağla
  Servo1.attach(9);
  Servo1.write(servoCenter); // Servo başlangıçta merkez konumda başlat

  // Motor pinlerini çıkış olarak ayarla
  pinMode(EnL, OUTPUT);
  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);

  pinMode(EnR, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);

  // Zamanlayıcıyı başlat
  startTime = millis();
}

// İleri hareket fonksiyonu
void Forward()
{
  // Right motor ileri
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, 100);

  // Left motor ileri
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, 100);
}

// Geri hareket fonksiyonu
void Backward()
{
  // Right motor geri
  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnR, 100);

  // Left motor geri
  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnL, 100);
}

void loop() {
  /*
  // 5 saniyede bir Forward fonksiyonunu çağır
  if (millis() - startTime <= 240000) { // İlk 5 saniye ileri hareket
    Forward();
  } else {
    // 5 saniye geçtiğinde motorları durdur
    analogWrite(EnL, 0);
    analogWrite(EnR, 0);
  }

  // Serial porttan veri varsa oku
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Satır sonuna kadar oku
    resultValue = data.toInt(); // Gelen veriyi tam sayıya çevir

    // PID kontrol
    float error = resultValue;
    integral += error;
    float derivative = error - previousError;
    float pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // Servo açısını hesapla
    int servoAngle = servoCenter - pidOutput;

    // Servo açısını sınırlandır
    if (servoAngle > servoMax) servoAngle = servoMax;
    if (servoAngle < servoMin) servoAngle = servoMin;

    Servo1.write(servoAngle); // Servo motoru belirlenen açıya ayarla
    previousError = error;    // Hatanın önceki değeri
  }
  */

  
  distance = sonar.ping_cm();
  Serial.print("Mesafe = ");
  Serial.print(distance);
  Serial.println(" cm");


}
