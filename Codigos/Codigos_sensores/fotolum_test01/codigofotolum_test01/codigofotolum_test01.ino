#include "heltec.h"

int pinoLed = 12; //PINO DIGITAL UTILIZADO PELO LED 
int pinoLDR = 4; //PINO ANALÓGICO UTILIZADO PELO LDR

void setup(){  
  Serial.begin(115200);
  Serial.println();
  Serial.println("configurando...");
  delay(6000);
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA 
  pinMode(pinoLDR, INPUT); //DEFINE O PINO COMO ENTRADA
}    
void loop(){
  //O VALOR 600 PODE SER AJUSTADO
  if(analogRead(pinoLDR) >= 400){ //SE O VALOR LIDO FOR MAIOR QUE 600, FAZ
    digitalWrite(pinoLed, HIGH); //ACENDE O LED
    printf("led acesa \n");
  }  
  else{ //SENÃO, FAZ
    digitalWrite(pinoLed, LOW); //APAGA O LED
    printf("led desligada \n");
  }  
  delay(5000);
}
