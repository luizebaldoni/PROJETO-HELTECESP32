// bibliotecas
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <heltec.h>
#include <DHT.h>

#define DHTPIN 2 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#define sensorvcc 0    // define vcc(+) como pino 0
#define sensorsinal 2  // Define sinal como pino 4

// dando nome a rede e uma senha
const char *ssid = "ESP32"; // nome da rede
const char *password = "carrinho"; // senha para acessar a rede
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
int dht_temp(){
  // pino que estamos conectados
  Serial.println("DHTxx test!");
  dht.begin();
 
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
    delay(2000);
  } 
  else
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print("% ");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println("ºC");
    delay(2000);
  }
}
int val = 0;
int agua(){/*abre laço de configuração*/
//#define sensorvcc 0    // define vcc(+) como pino 0
//#define sensorsinal 2  // Define sinal como pino 4 
  /* define 2 como pino de saída do Arduino */
  pinMode(sensorvcc, OUTPUT);
    val = analogRead(sensorsinal);    
  
  Serial.print("Nível de água: "); //printa o "Nível da água: " no monitor serial 
  Serial.println(val); //printa o nível da água no monitor serial 
  delay(5000);  //Atraso de 5s entre leituras
  }
// CONEXÃO COM O CLIENTE
void loop() {
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
    client.println(agua()); // faz retornar na tela do web server a função agua
    client.print("<p>TEMPERATURA E UMIDADE: </p>");
    client.println(dht_temp()); // faz retornar na tela do web server a função temp
    client.println("</html>");
    client.println("</body>");
    client.stop(); // fecha coneccao com o cliente
}
  }
  }
  }
  }
}
