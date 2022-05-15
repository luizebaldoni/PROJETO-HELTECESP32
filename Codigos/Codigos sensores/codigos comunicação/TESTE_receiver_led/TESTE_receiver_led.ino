#include "heltec.h"
 
#define BAND 433E6
char st;
void setup () {
Heltec.begin(true, true, true, true, BAND);
pinMode(12, OUTPUT);
}
 
void loop () {
int packetSize = LoRa.parsePacket();
 
if(packetSize) {
Serial.print("Pacote recebido '");
 
while(LoRa.available ()) {
st = (char)LoRa.read ();
Serial.println(st);
}
 
if (st == '1')
digitalWrite(12,HIGH);
delay(1000);
digitalWrite(12,LOW);
 
Serial.print("'com RSSI");
Serial.println(LoRa.packetRssi());
}
}
