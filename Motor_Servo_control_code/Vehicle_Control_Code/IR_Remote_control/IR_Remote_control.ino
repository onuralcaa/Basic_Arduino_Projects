//Yeni versiyon
#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11

void setup()
{
  Serial.begin(57600); // // Establish serial communication
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
      // 0 veya 1 değerlerini filtrele
      if (IrReceiver.decodedIRData.decodedRawData > 1) {
          Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print data except 0 and 1
      }
      IrReceiver.resume(); // Enable receiving of the next value
  }
}
