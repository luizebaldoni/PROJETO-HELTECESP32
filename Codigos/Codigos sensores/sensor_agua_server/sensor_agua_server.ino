//BIBLIOTECAS
#include "heltec.h"
#include "arduino.h"

//DEFINICOES
int pinosensor = 4;       // Pino conectado ao sensor
int pinoLED = 12; // Pino conectado à LED

//CODIGO PRINCIPAL
String sinais; // Variável para enviar os sinais
void setup() {
  Serial.begin(9600); //Inicia comunicação serial    
  delay(6000); // Aguarda o sensor armar       
  pinMode(pinosensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA    
}

//CONDICOES
void loop() {
  if(analogRead(pinosensor) > 690){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      digitalWrite(pinoLED, HIGH); //ACENDE O LED
  }else{ //SENÃO, EXECUTA:
    digitalWrite(pinoLED, LOW); //DESLIGA O LED
  }
  // Verificando erros
  if (isnan(pinosensor) || isnan(pinoLED)) {    
    return;
  }
  //Linha que envia os sinais do sensor via Serial para gravar no BD
  sinais = String(pinosensor) + "|" + String(pinoLED);
  Serial.println(sinais);
  delay(30000); //Aguarda 30 segundos

}
