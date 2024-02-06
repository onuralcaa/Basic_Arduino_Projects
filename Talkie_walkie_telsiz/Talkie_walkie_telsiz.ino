



#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include "printf.h"

RF24 radio(7,8); 
RF24Audio rfAudio(radio,0);

int talkButton = 3;

void setup() { 
Serial.begin(115200);

printf_begin();
radio.begin();
radio.printDetails();
rfAudio.begin();

pinMode(talkButton, INPUT);

//sets interrupt to check for button talk abutton press
attachInterrupt(digitalPinToInterrupt(talkButton), talk, CHANGE);

//sets the default state for each module to recevie
rfAudio.receive();

}



void talk()
{ 
if (digitalRead(talkButton)){ rfAudio.transmit();
delay(10);
}
else { rfAudio.receive();
delay(10); 
}
}


void loop()
{
}
