#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// substitua os dados entre parênteses com o nome da Rede e a senha desejados
const char *ssid = "ESP32";
const char *password = "carrinho";

WiFiServer server(80);

//Confugurações dos pinos

const int pinoLED = 12;

void setup() {
  
pinMode(pinoLED, OUTPUT);

Serial.begin(115200);
Serial.println();
Serial.println("configurando...");


// Você pode remover o parâmetro de senha se quiser que
// a rede gerada seja aberta.
WiFi.softAP(ssid, password);
IPAddress myIP = WiFi.softAPIP();
Serial.print("O Endereço IP Da Rede : ");
Serial.println(myIP);
//inicia o webserver
server.begin();

Serial.println("Servidor Iniciado!!");


}

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
client.println("HTTP/1.1 200 OK");
client.println  ("Content-type:text/html");
client.println();
 client:send("<head><meta http-equiv='refresh' content='1'></head>") 
        client:send("<h1>Recebendo dados da porta analógica</h1>")
        client:send("<p>Valor da porta analógica:</p>")
        client:send(adc.read(0)) //Envia o valor do sensor
        client:send("<p>A página é atualizada sozinha</p>")

client.println();
break;
} else { 
currentLine = "";
}
} else if (c != '\r') { 
currentLine += c; 
}
}

client.stop();


}
