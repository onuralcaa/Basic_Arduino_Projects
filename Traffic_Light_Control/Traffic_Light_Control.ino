#include <IRremote.hpp>  // IRremote kütüphanesini dahil et

#define IR_RECEIVE_PIN 2  // IR sensörünü D2 pinine bağla

// LED Pinleri
#define RED_LED 4     // Kırmızı LED D3 pininde
#define YELLOW_LED 8  // Sarı LED D4 pininde
#define GREEN_LED 6   // Yeşil LED D5 pininde

// IR Kodları
#define BUTTON_3 0xB847FF00  // 3'ün kodu (Kırmızı LED)
#define BUTTON_6 0xBC43FF00  // 6'nın kodu (Kırmızı + Sarı LED)
#define BUTTON_9 0xF609FF00  // 9'un kodu (Yeşil LED)

void setup() {
  Serial.begin(9600);  // Seri iletişimi başlat
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // IR alıcıyı başlat
  
  // LED pinlerini çıkış olarak ayarla
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // Tüm LED'leri başlangıçta kapat
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  
  Serial.println("IR komutlari bekleniyor...");
}

void loop() {
  if (IrReceiver.decode()) {  // IR sinyali alındıysa
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;  // IR kodunu al
    Serial.print("Kod: 0x");
    Serial.println(irCode, HEX);  // IR kodunu HEX formatında yazdır
    
    // LED Kontrolleri
    if (irCode == BUTTON_3) {  // 3'e basıldıysa
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    } 
    else if (irCode == BUTTON_6) {  // 6'ya basıldıysa
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    } 
    else if (irCode == BUTTON_9) {  // 9'a basıldıysa
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
    }
    
    IrReceiver.resume();  // Yeni sinyal beklemeye geç
  }
}
