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

// İleri Hareket
void Forward(int speed = 100) {
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, speed);

  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, speed);
}

// Geri Hareket
void Backward(int speed = 100) {
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
void TurnLeft(int durationMs) {
  Servo1.write(servoMax); // Sola dön
  Forward();              
  delay(durationMs);
  Servo1.write(servoCenter); 
  MotorStop();
}

// Sağa Dönüş
void TurnRightBack(int durationMs) {
  Servo1.write(servoMin); // Sağa dön
  Backward();             
  delay(durationMs);      
  Servo1.write(servoCenter); 
  MotorStop();            
}

// U Dönüşü
void PerformUTurn() {
  Forward();
  delay(750); 

  // Sola dönerek U dönüşü yap
  TurnLeft(1200); 
  TurnRightBack(1200);
  TurnLeft(1500); 

  MotorStop();
  delay(2000);
}

// **IR Komutlarını İşle**
void handleIRCommand(unsigned long command) {
  if (command == BUTTON_1) { // Manuel Mod
    otonomMod = false;
    MotorStop(); // Manuel moda geçerken motorları durdur
  }
  else if (command == BUTTON_2) { // Otonom Mod
    otonomMod = true; // Otonom moda geç
    Servo1.write(servoCenter); 
    MotorStop(); 
  }
  else if (!otonomMod) { // Manuel Mod Kontrolleri
    if (command == BUTTON_UP) { // İleri Git
      Forward();
      lastCommandTime = millis(); 
    }
    else if (command == BUTTON_DOWN) { // Geri Git
      Backward();
      lastCommandTime = millis(); 
    }
    else if (command == BUTTON_RIGHT) { // Sağa Dön
      Servo1.write(servoMin);
    }
    else if (command == BUTTON_LEFT) { // Sola Dön
      Servo1.write(servoMax);
    }
    else if (command == BUTTON_OK) { // Ortaya Dön
      Servo1.write(servoCenter);
    }
  }
}

// **Kurulum**
void setup() {
  Serial.begin(9600); // Seri haberleşme
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
  // IR Kodlarını Kontrol Et
  if (IrReceiver.decode()) {
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;
    if (irCode > 1) { 
      handleIRCommand(irCode); 
    }
    IrReceiver.resume(); 
  }

  // Manuel Mod Kontrolü
  if (!otonomMod && millis() - lastCommandTime > 500) {
    MotorStop();
  }

  // Otonom Mod Kontrolü
  if (otonomMod) {
    distance = sonar.ping_cm(); 

    if (distance > 10) {
      Forward(); 

      // U dönüş kontrolü
      if (uTurnActive) {
        PerformUTurn();
        if (millis() - uTurnStartTime > 4500) { 
          uTurnActive = false;
        }
        return; 
      }

      // Raspberry Pi'den Gelen Veriyi Kontrol Et
      if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');

        if (data == "TURN") { // U dönüş komutu
          uTurnActive = true;
          uTurnStartTime = millis();
        } else {
          resultValue = data.toInt(); 
        }
      }

      // Servo Açısını Ayarla
      int servoAngle = servoCenter - resultValue;
      servoAngle = constrain(servoAngle, servoMin, servoMax);
      Servo1.write(servoAngle);
    } 
    else {
      MotorStop();
    }
  }
}
