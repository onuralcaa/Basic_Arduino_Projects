#include "LoRa_E32.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial);
 
struct Signal {
  char type[15];
  byte temp[4];
} data;
 
void setup() {
  Serial.begin(9600);
  e32ttl.begin();
  delay(500);
}
 
void loop() {
  while (e32ttl.available()  > 1) {
 
    // Gelen mesaj okunuyor
    ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    Serial.print("Gelen Messaj: ");
    Serial.println(data.type);
    rsc.close();
 
    //Gönderilecek paket veri hazırlanıyor
    struct Signal  {
      char type[15] = "Bebek Odası";
      byte temp[4];
    } data2;
 
    *(float*)(data2.temp) = 19.2;
 
 
    ResponseStatus rs = e32ttl.sendFixedMessage(0, 63, 23, &data2, sizeof(Signal));
    Serial.println(rs.getResponseDescription());
 
  }
 
}
