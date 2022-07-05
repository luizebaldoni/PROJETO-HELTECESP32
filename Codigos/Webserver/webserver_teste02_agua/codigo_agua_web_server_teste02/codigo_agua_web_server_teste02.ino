#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <heltec.h>

const char *ssid = "ESP32";
const char *password = "Teste03";
//DEFINICOES
int pinosensor = 4;      
int pinoLED = 12;
WiFiServer server(80);
//CODIGO PRINCIPAL
void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); 
  pinMode(pinosensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA    
  WiFi.softAP(ssid, password); // DEFINE que para ter acesso precisa senha
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("O Endereço IP Da Rede : ");
  Serial.println(myIP);
  server.begin(); //inicia o webserver
  Serial.println("Servidor Iniciado!!");
}
boolean sensor(){
  if (analogRead(pinosensor) > 690){
    digitalWrite(pinoLED, HIGH);
  }
}
//CONDICOES
void loop(){
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
                if(sensor() == true){
                  client.println("<p>Leitura do sensor eh maior que 690 bits</p>");
                }else
                  client.println("<p>Leitura menor que 690 bits ou sensor desligado</p>");
                }
              client.println("</html>");
              client.println("</body>");
              client.stop();
        }
        }
      }
    }
  }
