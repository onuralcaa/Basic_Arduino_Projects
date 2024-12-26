#include <Servo.h>
#include "NewPing.h"
#include <IRremote.hpp>

// IR Sensör Tanımlamaları
#define IR_RECEIVE_PIN 11

// HCSR04 Mesafe Sensör Tanımları
#define ECHO_PIN 13
#define TRIGGER_PIN 12
#define MAX_DISTANCE 400
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float distance;

// Servo Tanımlamaları
Servo Servo1;

// Servo Limitleri
const int servoMin = 55;
const int servoMax = 135;
const int servoCenter = 95;

// Motor Pinleri
const int EnL = 5;
const int HighL = 6;
const int LowL = 7;
const int EnR = 3;
const int HighR = 2;
const int LowR = 4;

// Mod ve Kontrol Değişkenleri
bool otonomMod = false;       // Başlangıçta otonom mod
unsigned long uTurnStartTime;
bool uTurnActive = false;
int resultValue = 0;         // Raspberry Pi'den gelen açı değeri

// IR Tuş Kodları
#define BUTTON_1 0xBA45FF00
#define BUTTON_2 0xB946FF00
#define BUTTON_UP 0xE718FF00
#define BUTTON_DOWN 0xAD52FF00
#define BUTTON_RIGHT 0xA55AFF00
#define BUTTON_LEFT 0xF708FF00
#define BUTTON_OK 0xE31CFF00

void setup() {
  Serial.begin(57600); // Seri Haberleşme Hızı

  // IR Alıcıyı Başlat
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  // Mesafe Sensörü Pinleri
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Servo Motor
  Servo1.attach(9);
  Servo1.write(servoCenter); // Başlangıçta ortada

  // Motor Pinleri
  pinMode(EnL, OUTPUT);
  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);
  pinMode(EnR, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);
}

// İleri Hareket
void Forward(int speed = 95) {
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, speed);

  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, speed);
}

// Geri Hareket
void Backward(int speed = 95) {
  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnR, speed);

  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnL, speed);
}

// Araç Durdur
void MotorStop() {
  analogWrite(EnR, 0);
  analogWrite(EnL, 0);
}

// Sola Dön
void TurnLeft() {
  Servo1.write(servoMax);
}

// Sağa Dön
void TurnRight() {
  Servo1.write(servoMin);
}

// Orta Pozisyona Dön
void CenterServo() {
  Servo1.write(servoCenter);
}

// U Dönüşü
void PerformUTurn() {
  Forward(95);
  delay(750);

  Servo1.write(servoMax);
  delay(1200);
  Servo1.write(servoMin);
  delay(1200);
  Servo1.write(servoMax);
  delay(1500);

  MotorStop();
  delay(2000);
}

// IR Komutlarını İşle
void handleIRCommand(unsigned long command) {
  if (command == BUTTON_1) { // Kumanda Modu
    otonomMod = false;
    //Serial.println("Kumanda Modu Aktif!");
  }
  else if (command == BUTTON_2) { // Otonom Mod
    otonomMod = true;
    //Serial.println("Otonom Mod Aktif!");
  }
  else if (!otonomMod) { // Kumanda Modunda Kontroller
    if (command == BUTTON_UP) { // İleri Git
      Forward();
      delay(500);
      MotorStop();
    }
    else if (command == BUTTON_DOWN) { // Geri Git
      Backward();
      delay(500);
      MotorStop();
    }
    else if (command == BUTTON_RIGHT) { // Sağa Dön
      TurnRight();
    }
    else if (command == BUTTON_LEFT) { // Sola Dön
      TurnLeft();
    }
    else if (command == BUTTON_OK) { // Ortaya Dön
      CenterServo();
    }
  }
}

// Ana Döngü
void loop() {
  // IR Kodlarını Kontrol Et
  if (IrReceiver.decode()) {
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;
    if (irCode > 1) { // Geçerli bir IR kodu
      Serial.print("IR Kodu: ");
      Serial.println(irCode, HEX);
      handleIRCommand(irCode); // Komutu işle
    }
    IrReceiver.resume(); // Yeni veri almak için hazırla
  }

  // Otonom Modda Çalıştır
  if (otonomMod) {
    distance = sonar.ping_cm(); // Mesafe Sensörü Kontrolü
    if (distance > 10) {
      Forward(); // İleri hareket

      // Seri Porttan Veri Al
      if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        if (data == "TURN") {
          uTurnActive = true;
          uTurnStartTime = millis();
        } else {
          resultValue = data.toInt();
        }
      }

      // Gelen açı değeri ile servo ayarla
      float error = resultValue;
      int servoAngle = servoCenter - error;

      // Servo sınırlarını kontrol et
      if (servoAngle > servoMax) servoAngle = servoMax;
      if (servoAngle < servoMin) servoAngle = servoMin;

      Servo1.write(servoAngle);
    } else {
      MotorStop(); // Engel varsa dur
    }

    // U Dönüşü Kontrolü
    if (uTurnActive) {
      PerformUTurn();
      if (millis() - uTurnStartTime > 5500) {
        uTurnActive = false;
      }
    }
  }
}
