#include "heltec.h"

#define sensorvcc 0    // define vcc(+) como pino 2 
#define sensorsinal 4  // Define sinal como pino 4 

int val = 0;
int agua(){   //abre laço de configuração
  
  pinMode(sensorvcc, OUTPUT); //define 4 como pino de saída do Arduino
  Serial.begin(9600);  
    val = analogRead(sensorsinal);    
    // imprimindo na tela os valores: 
  Serial.print("Nível de água: "); 
  Serial.println(val); //imprime na tela o nível da água no monitor serial 
  delay(5000);  // Espera 5 segundos e le dnv o sensor
  }
