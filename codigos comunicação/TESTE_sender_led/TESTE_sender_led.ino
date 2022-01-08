#include "heltec.h"
#define BAND 433E6

void setup () {
Heltec.begin(true, true, true, true, BAND);
}

void loop () {
Serial.print("Envio de pacote:");
Serial.println(contador);

LoRa.beginPacket();
LoRa.print(digitalRead(12));
LoRa.endPacket();

digitalWrite(25, HIGH);
delay(400);
digitalWrite(25, LOW);
delay(400);
}
