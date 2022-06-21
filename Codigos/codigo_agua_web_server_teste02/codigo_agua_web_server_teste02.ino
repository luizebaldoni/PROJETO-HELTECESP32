#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <heltec.h>

const char *ssid = "ESP32";
const char *password = "Teste03";
//DEFINICOES
const int pinosensor = 4;      
const int pinoLED = 12; 
WiFiServer server(80);
//CODIGO PRINCIPAL
void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); 
  pinMode(pinosensor, INPUT); 
  pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA    
  WiFi.softAP(ssid, password); // DEFINE que para ter acesso precisa senha
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("O Endereço IP Da Rede : ");
  Serial.println(myIP);
  server.begin(); //inicia o webserver
  Serial.println("Servidor Iniciado!!");


}
//CONDICOES
void loop(){
  if(analogRead(pinosensor) > 690){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      digitalWrite(pinoLED, HIGH); //ACENDE O LED
  }else{ //SENÃO, EXECUTA:
    digitalWrite(pinoLED, LOW); //DESLIGA O LED
  }
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
    if (analogRead(pinosensor) >= 690){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      client.println("<p>A leitura do sensor eh maior q 690 bits</p>");
      }else if(analogRead(pinosensor) < 690){ 
        client.println("<p>A leitura do sensor eh menor que 690 bits</p>");
      } else{
        client.println("<p>Nao foi possivel ler o sensor</p>");
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
