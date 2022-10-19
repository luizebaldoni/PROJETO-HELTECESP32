// CODIGO PARA HELTEC ESP 32

//biblioteca
#include <DHT.h>

//definições
#define DHTPIN 15  // pino analogico do dht11
#define DHTTYPE DHT11 // DHT 11
#define led 12 // pino digital da led
#define sensor 2 // pino analogico do fotoresistor
#define sensorsinal 17 // pino analogico do sensor de agua

//valores:
int val = 0;  // valor incia em 0
int limiteDisparo = 5000;  // valores abaixo de 700 led vai liagr
int sensorValue = 0; // Armazena o valor de leitura analógica

DHT dht(DHTPIN, DHTTYPE);  // definições do dht11

void setup(){
  Serial.begin(9600);  // iniciando serial
  dht.begin();   // iniciando sensor dht
  
  // modo dos pinos do circuito fotoresistor: 
  pinMode(led, OUTPUT);// Define o LED como uma saída
  pinMode(sensor, INPUT);// Define o fotoresistor como uma entrada

}
// codigo principal
void loop(){
  
  // SENSOR DE AGUA:
  val = analogRead(sensorsinal);  // define q a leitura vai ser do pino analogico sensorsinal
    
  // printa o nível da água no monitor serial 
  Serial.println("       ");  // dando espaço p fciar mais bonito no monitor erial
  Serial.println("Executando medição do nivel da agua... ");
  delay(2000);  // espera dois segundos e executa: 
  Serial.print("Nível de água: ");  
  Serial.println(val);   // chama o val para mostrar o valor do sensor
  delay(2000); // espera dois segundos e executa sensor de temperatura 

  
  // SENSOR DE TEMPERATURA:
  Serial.println("       "); // dando espaço p fciar mais bonito no monitor erial
  Serial.println("Executando medição da temeratura e umidade... ");
  delay(2000); // espera dois segundos e executa: 
  
  float h = dht.readHumidity();  // definindo h como variavel para leitura da umidade pelo dht
  float t = dht.readTemperature(); // definindo t como variavel para leitura da temperatura pelo dht
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Nao foi possivel ler o sensor DHT11");
    delay(2000); // espera dois segundos e executa: 
  } 
  else
  {
    //mostrado no monitor serial resultado da medição: 
    Serial.print("Umidade: ");
    Serial.print(h); // imprimindo variavel da uidade
    Serial.print("% ");
    Serial.print("Temperatura: ");
    Serial.print(t);  // imprimindo variave da temperatura
    Serial.println("ºC");  
} delay(2000); // espera dois segundos e executa o fotoresistor 


  // SENSOR FOTORESISTOR
  Serial.println("       "); // dando espaço p fciar mais bonito no monitor erial
  Serial.println("Executando medição do Fotoresistor... ");
  
  delay(2000);  // espera dois segundos e executa: 
  sensorValue = analogRead(sensor);// Lê o valor atual do fotoresistor
  
  // Se o valor estiver abaixo de um determinado "limite de disparo", 
  //então o LED liga, caso contrário o LED permanece desligado
  if (sensorValue < limiteDisparo) {  // se o valor do sensor for menor q o limite a led iga
      digitalWrite(led, HIGH);
  }
  else { // se nao for led aaga
      digitalWrite(led,LOW);
  }
  // mostrabdo no monitor serial: 
  Serial.print ("Luminosidade: ");
  Serial.println(sensorValue);  
delay(5000); // espera 5 segundos e executa dnv
}
