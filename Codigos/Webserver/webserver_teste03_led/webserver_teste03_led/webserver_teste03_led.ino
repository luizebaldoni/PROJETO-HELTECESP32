#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <heltec.h>

const char *ssid = "ESP32"; // nome da rede
const char *password = "carrinho"; // senha para acessar a rede
//DEFINICOES 
  int valor_sensor = analogRead(4); // pino analogico do sensor
WiFiServer server(80);
//CODIGO PRINCIPAL
void setup() {
  Serial.begin(115200); // velocidade serial
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); 
  pinMode(4, INPUT);
  WiFi.softAP(ssid, password); // DEFINE que para ter acesso precisa senha
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("O Endereço IP Da Rede : "); // mostrando no monitor serial o endereço do server
  Serial.println(myIP);
  server.begin(); //inicia o webserver
  Serial.println("Servidor Iniciado!!");


}
void loop() {
  // abrindo coneccao cliente/servidor
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
      client.print("<p>Informacoes do sensor de agua:</p>");
     if (valor_sensor >= 690){ // colocando a condiçao que faz o sensor funcionar
      client.println("<li>A leitura do sensor e maior que 690 bits</li>"); // imprime na tela
      }else{ // se nao for a condicao inicial:
        client.print("<li>A leitura do sensor e menor que 690 bits ou sensor desligado!</li>"); // imprime na tela
        }
    client.println("</html>");
    client.println("</body>");
    client.stop(); // fecha coneccao com o cliente
}
  }
  }
  }
  }
}
