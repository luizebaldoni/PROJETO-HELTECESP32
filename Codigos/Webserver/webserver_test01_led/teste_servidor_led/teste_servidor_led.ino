#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "heltec.h"

const char *ssid = "ESP32";
const char *password = "Teste03";
//DEFINICOES    
int pino = 12; 
WiFiServer server(80);
//CODIGO PRINCIPAL
void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); 
  pinMode(12, OUTPUT); //DEFINE O PINO COMO SAÍDA    
  WiFi.softAP(ssid, password); // DEFINE que para ter acesso precisa senha
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("O Endereço IP Da Rede : ");
  Serial.println(myIP);
  server.begin(); //inicia o webserver
  Serial.println("Servidor Iniciado!!");


}
//CONDICOES
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
    client.println("Content-type:text/html");
    client.println();
    client.println("<html>");
    client.print("<head><title> Servidor ESP32 </title></head>");
    client.print("<body>");
    client.print("<style type=\"text/css\">h1{color: black;font-family: 'Times New Roman', Times, serif; }.ligado{background-color: green;color: aliceblue;}</style>");
    client.println("<h1>Recebendo dados da porta analogica</h1>");
    client.println("<p class="">Valor da porta analógica:</p>");
    if (digitalRead((pino)== HIGH)){ 
      client.println("<p class=\"ligado\">A LED esta ligada</p>");
      }else{ 
        client.println("<p class=\"desligado\">A LED esta desligada!</p>");
      }
    client.println("</html>");
    client.println("</body>");
    client.stop();
}
  }
  }
  }
  }
}
