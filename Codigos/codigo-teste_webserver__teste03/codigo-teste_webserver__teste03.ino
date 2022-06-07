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
  pinMode(12, INPUT_PULLUP); //DEFINE O PINO COMO SAÍDA    
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
    client.println("<head><meta http-equiv='refresh' content='1'><tittle>Servidor ESP32</tittle></head>");
    client.println("<h1>Recebendo dados da porta analogica</h1>");
    client.println("<p>Valor da porta analógica:</p>");
    if (digitalWrite(12, HIGH)){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      client.println("<p>A LED esta ligada</p>");
      }else{ 
        client.println("<p>A LED esta desligada!</p>");
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
