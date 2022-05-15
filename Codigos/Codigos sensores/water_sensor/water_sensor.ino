//BIBLIOTECAS
#include "arduino.h" 
#include "heltec.h"

int pinoSensor = 4; //PINO ANALÓGICO UTILIZADO PELO SENSOR
int pinoLED = 12; //DEFININDO PINO DA LED
               
void setup(){
  //Serial.begin(9600); //INICIALIZAÇÃO DA SERIAL
   pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
   pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA
}

void loop(){
  if(analogRead(pinoSensor) > 690){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      digitalWrite(pinoLED, HIGH); //ACENDE O LED
  }else{ //SENÃO, EXECUTA:
    digitalWrite(pinoLED, LOW); //DESLIGA O LED
  }
 }
