#include "heltec.h"
int val = 0;
int agua(){/*abre laço de configuração*/
  /* define 2 como pino de saída do Arduino */
  pinMode(sensorvcc, OUTPUT);
  Serial.begin(9600); /* Baudrate de 9600 */
    val = analogRead(sensorsinal);    
  /*printa o nível da água no monitor serial */
  Serial.print("Nível de água: "); /*printa o "Nível da água: " no monitor serial */
  Serial.println(val); /*printa o nível da água no monitor serial */
  delay(5000);  /*Atraso de 5s entre leituras*/
  }
