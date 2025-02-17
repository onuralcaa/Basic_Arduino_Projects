#include <Servo.h>
#include "NewPing.h"
#include <IRremote.hpp>

// IR Sensör Tanımlamaları
#define IR_RECEIVE_PIN 2

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
const int HighL = 3;
const int LowL = 4;

const int EnR = 6;
const int HighR = 8;
const int LowR = 7;

// Mod ve Kontrol Değişkenleri
bool otonomMod = false;       // Varsayılan manuel mod
unsigned long lastCommandTime = 0;
int resultValue = 0;          // Raspberry Pi'den gelen açı değeri
int motorSpeed = 150;         // **Motor hızı başlangıçta manuel mod için 150 olarak ayarlandı**

// U dönüş değişkenleri
bool uTurnActive = false;       // U dönüşü aktif mi?
unsigned long uTurnStartTime;   // U dönüşü başlangıç zamanı

// IR Tuş Kodları
#define BUTTON_1 0xBA45FF00 // Manuel Mod
#define BUTTON_2 0xB946FF00 // Otonom Mod
#define BUTTON_UP 0xE718FF00
#define BUTTON_DOWN 0xAD52FF00
#define BUTTON_RIGHT 0xA55AFF00
#define BUTTON_LEFT 0xF708FF00
#define BUTTON_OK 0xE31CFF00

// **Fonksiyonlar**

// 🚗 **İleri Hareket**
void Forward() {
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, motorSpeed);  // **Güncellenen motor hızını kullan**

  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, motorSpeed);  // **Güncellenen motor hızını kullan**
}

// 🔄 **Geri Hareket**
void Backward() {
  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnR, motorSpeed);  

  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnL, motorSpeed);
}

// 🛑 **Araç Durdur**
void MotorStop() {
  analogWrite(EnR, 0);
  analogWrite(EnL, 0);
}

// 🔄 **Sola Dön**
void TurnLeft(int durationMs) {
  Servo1.write(servoMax); 
  Forward();              
  delay(durationMs);
  Servo1.write(servoCenter); 
  MotorStop();
}

// 🔁 **Sağa Dönüş**
void TurnRightBack(int durationMs) {
  Servo1.write(servoMin); 
  Backward();             
  delay(durationMs);      
  Servo1.write(servoCenter); 
  MotorStop();            
}

// ⭕ **U Dönüşü**
void PerformUTurn() {
  Forward();
  delay(750); 

  TurnLeft(1200); 
  TurnRightBack(1200);
  TurnLeft(1500); 

  MotorStop();
  delay(2000);
}

// **IR Komutlarını İşle**
void handleIRCommand(unsigned long command) {
  if (command == BUTTON_1) { // **Manuel Mod**
    otonomMod = false;
    motorSpeed = 150; // **Manuel modda hız 150**
    MotorStop();
  }
  else if (command == BUTTON_2) { // **Otonom Mod**
    otonomMod = true;
    motorSpeed = 120; // **Otonom modda hız 120**
    Servo1.write(servoCenter); 
    MotorStop();
  }
  else if (!otonomMod) { // **Manuel Mod Kontrolleri**
    if (command == BUTTON_UP) { 
      Forward();
      lastCommandTime = millis(); 
    }
    else if (command == BUTTON_DOWN) { 
      Backward();
      lastCommandTime = millis(); 
    }
    else if (command == BUTTON_RIGHT) { 
      Servo1.write(servoMin);
    }
    else if (command == BUTTON_LEFT) { 
      Servo1.write(servoMax);
    }
    else if (command == BUTTON_OK) { 
      Servo1.write(servoCenter);
    }
  }
}

// **Kurulum**
void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Servo1.attach(10);
  Servo1.write(servoCenter); 

  pinMode(EnL, OUTPUT);
  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);
  pinMode(EnR, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);
}

// **Ana Döngü**
void loop() {
  // 📡 **IR Kodlarını Kontrol Et**
  if (IrReceiver.decode()) {
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;
    if (irCode > 1) { 
      handleIRCommand(irCode); 
    }
    IrReceiver.resume(); 
  }

  // **Manuel Mod Kontrolü**
  if (!otonomMod && millis() - lastCommandTime > 500) {
    MotorStop();
  }

  // **Otonom Mod Kontrolü**
  if (otonomMod) {
    distance = sonar.ping_cm(); 

    if (distance > 10) {
      Forward(); 

      // ⭕ **U dönüş kontrolü**
      if (uTurnActive) {
        PerformUTurn();
        if (millis() - uTurnStartTime > 4500) { 
          uTurnActive = false;
        }
        return; 
      }

      // 🔄 **Raspberry Pi'den Gelen Veriyi Kontrol Et**
      if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');

        if (data == "TURN") { 
          uTurnActive = true;
          uTurnStartTime = millis();
        } else {
          resultValue = data.toInt(); 
        }
      }

      // **Servo Açısını Ayarla**
      int servoAngle = servoCenter - resultValue;
      servoAngle = constrain(servoAngle, servoMin, servoMax);
      Servo1.write(servoAngle);
    } 
    else {
      MotorStop();
    }
  }
}
