#include "arduino.h"

int pinoLed = 5; //PINO DIGITAL UTILIZADO PELO LED 
int pinoLDR = 17; //PINO ANALÓGICO UTILIZADO PELO LDR
int receber; 

void setup(){  
  Serial.begin(115200);
  Serial.println();
  Serial.println("configurando...");
  delay(6000);
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA 
  pinMode(pinoLDR, INPUT); //DEFINE O PINO COMO ENTRADA
}    
void loop(){
  receber = analogRead(pinoLDR);
  Serial.println(receber);
  //digitalWrite(pinoLed, HIGH);
  //O VALOR 600 PODE SER AJUSTADO
  if(receber >= 600){ //SE O VALOR LIDO FOR MAIOR QUE 600, FAZ
    digitalWrite(pinoLed, HIGH); //ACENDE O LED
    printf("led acesa \n");
  }  
  else{ //SENÃO, FAZ
    digitalWrite(pinoLed, LOW); //APAGA O LED
    printf("led desligada \n");
  }  
  delay(5000);
}
