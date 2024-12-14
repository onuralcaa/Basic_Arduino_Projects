#include <Servo.h>
#include "NewPing.h"

// HCSR04 sensor degiskenleri
#define ECHO_PIN 13
#define TRIGGER_PIN 12
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float duration, distance;

Servo Servo1;

int resultValue = 0; // Gelen değer için değişken
bool uTurnActive = false; // U dönüşü aktif mi?
unsigned long uTurnStartTime; // U dönüşü başlangıç zamanı

// Servo sınırları
int servoMin = 55;    // Servo minimum açısı (sağ)
int servoMax = 135;   // Servo maksimum açısı (sol)
int servoCenter = 95; // Servo merkezi (direksiyon sıfır konumu)

// Left motor pins
const int EnL = 5;
const int HighL = 6;
const int LowL = 7;

// Right motor pins
const int EnR = 3;
const int HighR = 2;
const int LowR = 4;

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
}

// İleri hareket fonksiyonu
void Forward() {
  // Right motor ileri
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, 125);

  // Left motor ileri
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, 125);
}

// Geri hareket fonksiyonu
void Backward() {
  // Right motor geri
  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnR, 125);

  // Left motor geri
  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnL, 125);
}

// Araç durdurma
void MotorStop() {
  analogWrite(EnR, 0);
  analogWrite(EnL, 0);
}

////////////////U dönüşü için////////////////////////////////////
// Sola dönme hareketi
void TurnLeft(int durationMs) {
  Servo1.write(servoMax); // Direksiyonu sola çevir
  Forward();              // İleri hareket
  delay(durationMs);      // Belirtilen süre kadar devam et
  Servo1.write(servoCenter); // Direksiyonu merkezle
  MotorStop();            // Araç durdur
}

// Sağa dönme hareketi
void TurnRight(int durationMs) {
  Servo1.write(servoMin); // Direksiyonu sağa çevir
  Backward();              // İleri hareket
  delay(durationMs);      // Belirtilen süre kadar devam et
  Servo1.write(servoCenter); // Direksiyonu merkezle
  MotorStop();            // Araç durdur
}

// U dönüşü hareketi
void PerformUTurn() {
  // Geri git
  Forward();
  delay(1500); // 1 saniye geri git

  // Sola dönerek U dönüşü yap
  TurnLeft(3000); // 3 saniye boyunca sola dön
  TurnRight(3000);
  TurnLeft(3000); // 3 saniye boyunca sola dön

  // Araç durdur
  MotorStop();
  delay(500); // Kısa duraklama
}
/////////////////////////////////////////////////////////////////
void loop() {
  // Mesafe sensörü verisi
  distance = sonar.ping_cm();

  // Seri porttan veri varsa oku
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Satır sonuna kadar oku

    if (data == "TURN") {
      uTurnActive = true;
      uTurnStartTime = millis(); // U dönüşü başlangıç zamanını kaydet
    } else {
      resultValue = data.toInt(); // Gelen veriyi tam sayıya çevir
    }
  }

  // Eğer U dönüşü aktifse, hareketleri yap
  if (uTurnActive) {
    PerformUTurn();

    // U dönüşü tamamlandıktan sonra aktif durumu kapat
    if (millis() - uTurnStartTime > 5000) { // 5 saniyelik U dönüşü süresi
      uTurnActive = false;
    }
    return; // U dönüşü sırasında diğer işlemleri durdur
  }

  // Normal şerit takip hareketleri
  if (distance > 10) {
    Forward();
  } else {
    MotorStop();
  }

  // Gelen PID kontrol komutlarına göre servo hareketi
  float error = resultValue;
  float pidOutput = error; // Direkt hata değeri servo açısı olarak alındı

  // Servo açısını hesapla
  int servoAngle = servoCenter - pidOutput;

  // Servo açısını sınırlandır
  if (servoAngle > servoMax) servoAngle = servoMax;
  if (servoAngle < servoMin) servoAngle = servoMin;

  Servo1.write(servoAngle); // Servo motoru belirlenen açıya ayarla
}
