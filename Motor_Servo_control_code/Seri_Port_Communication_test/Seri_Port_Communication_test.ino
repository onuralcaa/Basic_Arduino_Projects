#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int resultValue = 0; // Gelen değer için değişken

// LCD ekran tanımlama (adres: 0x27, 16x2 LCD için)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(57600); // Seri haberleşmeyi başlat
  lcd.begin(16, 2);    // LCD ekranı 16 sütun, 2 satır olarak başlat
  lcd.backlight();      // LCD arka ışığını aç
  lcd.print("Bekleniyor..."); // Başlangıç mesajı
}

void loop() {
  if (Serial.available() > 0) { // Veri varsa
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
