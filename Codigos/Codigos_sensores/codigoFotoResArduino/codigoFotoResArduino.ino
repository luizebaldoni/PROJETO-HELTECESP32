
// Pode ser necessário alterar o "valor limite de disparo" para encontrar um valor adequado
// para ligar e desligar o LED quando "mover a mão" sobre o fotoresistor (LDR)
int limiteDisparo = 600;
int led = 9;// Ligue o LED ao pino digital 9
int sensor = A0;// O fotoresistor (LDR) é conectado ao pino analógico 0
int sensorValue = 0; // Armazena o valor de leitura analógica

void setup() {
  pinMode(led, OUTPUT);// Define o LED como uma saída
  pinMode(sensor, INPUT);// Define o fotoresistor como uma entrada
  Serial.begin(9600);// Inicia a comunicação serial com uma taxa de transmissão de 9600 boud rate
}

void loop(){
  delay(2000);
  sensorValue = analogRead(sensor);// Lê o valor atual do fotoresistor
  
  // Se o valor estiver abaixo de um determinado "limite de disparo", então o LED liga, caso contrário o LED permanece desligado
  if (sensorValue < limiteDisparo) {
      digitalWrite(led, HIGH);
  }
  else {
      digitalWrite(led,LOW);
  }
  
  // Imprime as leituras atuais no monitor serial da IDE do Arduino
  Serial.print ("Luminosidade: ");
  Serial.println(sensorValue);
  delay(130);
}
