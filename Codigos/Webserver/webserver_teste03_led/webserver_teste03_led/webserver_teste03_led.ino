// bibliotecas
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <heltec.h>
#include <DHT.h>

// definições
#define DHTPIN 2 // pino analogico conectado
#define DHTTYPE DHT11 // DHT 11
#define sensorvcc 0    // define vcc(+) como pino 0
#define sensorsinal 4  // Define sinal como pino 4 

// dando nome a rede e uma senha
const char *ssid = "ESP32"; // nome da rede
const char *password = "carrinho"; // senha para acessar a rede

// função para executar sensor de agua:
int val = 0;
int agua(){   //abre laço de configuração
  
  pinMode(sensorvcc, OUTPUT); //define 4 como pino de saída do Arduino
  
  Serial.begin(9600);  // velocidade do serial
  
    val = analogRead(sensorsinal);  
      
    // imprimindo na tela os valores: 
  Serial.print("Nível de água: "); 
  Serial.println(val); //imprime na tela o nível da água no monitor serial 
  delay(5000);  // Espera 5 segundos e le dnv o sensor
  }
// função para executar sensor de temperatura e umidade
DHT dht(DHTPIN, DHTTYPE);

int temp(){
  Serial.begin(9600); // velocidade do serial
  dht.begin();
  
  float h = dht.readHumidity(); // definindo humidade
  float t = dht.readTemperature(); // definindo temperatura
  
  // testa se retorno é valido
  if (isnan(t) || isnan(h)) 
  {
    // caso seja invalido o retorno imprime na tela:
    Serial.println("Conexão com DHT11 **FALHOU**");
    
    delay(2000); // espera 2 segundos e tenta dnv
  } 
  else // caso o teste seja valido, executa:
  {
    Serial.print("Umidade: "); // imrpimindo umidade
    Serial.print(h);
    Serial.print("% "); // fazendo imprimir o % apos o valor
    Serial.print("Temperatura: "); //  definindo temperatura
    Serial.print(t);
    Serial.println("ºC"); //  fazendo imprimir q é em Celsius
    
    delay(2000); // espera 2 segundos executa dnv
  }
  }
  
// INICIANDO O WEB SERVER

WiFiServer server(80);
void setup() {
  Serial.begin(9600); // velocidade do serial
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); // espera 6 segundos
  
  WiFi.softAP(ssid, password); // DEFINE que para ter acesso a rede precisa de senha
  IPAddress myIP = WiFi.softAPIP();
  
  Serial.print("O Endereço IP Da Rede : "); // mostrando no monitor serial o endereço do server (q é o proprio ip da rede)
  Serial.println(myIP);
  server.begin(); //inicia o webserver
  Serial.println("Servidor Iniciado!!"); 

}
// CONEXÃO COM O CLIENTE
void loop() {
  
  // verificando se há um cliente
  
  WiFiClient client = server.available(); 
  if (client) { 
    Serial.println("Novo Cliente."); 
    String currentLine = ""; 
  while (client.connected()) { 
   if (client.available()) { 
    char c = client.read(); 
      Serial.write(c); 
  if (c == '\n') { 
  if (currentLine.length() == 0) {
    
    // criando html do setrvidor
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html>");
    client.print("<head><title> Servidor ESP32 </title></head>");
    client.print("<body>");
    client.print("<style type=\"text/css\">h1{color: black;font-family: 'Times New Roman', Times, serif; }.ligado{background-color: green;color: aliceblue;}</style>");
    client.print("<h1>RECEPCAO DE DADOS</h1>");
    client.print("<p>Sensores de Agua, umidade e temperatura</p>");
    client.print("<p>NIVEL DA AGUA: </p>");
    client.print(agua); // faz retornar na tela do web server a função agua
    client.print("<p>UMIDADE E TEMPERATURA: </p>");
    client.print(temp); // faz retornar na tela do web server a função temp
    client.println("</html>");
    client.println("</body>");
    client.stop(); // fecha coneccao com o cliente
}
  }
  }
  }
  }
}
