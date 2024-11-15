#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD ekran tanımlama (adres: 0x27, 16x2 LCD için)
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo Servo1;

int resultValue = 0; // Gelen değer için değişken

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
  lcd.begin(16, 2);    // LCD ekranı 16 sütun, 2 satır olarak başlat
  lcd.backlight();      // LCD arka ışığını aç
  lcd.print("Bekleniyor..."); // Başlangıç mesajı

  // Servo motoru pin 9'a bağla
  Servo1.attach(9);

  // Motor pinlerini çıkış olarak ayarla
  pinMode(EnL, OUTPUT);
  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);

  pinMode(EnR, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);
}

// İleri hareket fonksiyonu
void Forward()
{
  // Right motor ileri
  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  analogWrite(EnR, 150);

  // Left motor ileri
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  analogWrite(EnL, 150);
}

// Geri hareket fonksiyonu
void Backward()
{
  // Right motor geri
  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  analogWrite(EnR, 150);

  // Left motor geri
  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  analogWrite(EnL, 150);
}

void loop() {
  // Serial porttan veri varsa oku
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Satır sonuna kadar oku
    resultValue = data.toInt(); // Gelen veriyi tam sayıya çevir

    // Ekranı temizle ve yeni gelen değeri yazdır
    lcd.clear();
    lcd.setCursor(0, 0);            // İlk satır, ilk sütuna konumlan
    lcd.print("Result: ");           // "Result:" ifadesini yazdır
    lcd.setCursor(8, 0);             // İlk satır, 8. sütuna konumlan
    lcd.print(resultValue);          // Gelen değeri yazdır

    // Debug amaçlı Seri Monitöre de yazdır
    Serial.print("Result: ");
    Serial.println(resultValue);
  }
}
