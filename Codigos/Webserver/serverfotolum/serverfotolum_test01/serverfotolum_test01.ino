#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <heltec.h>

const int pinoLed = 13; //PINO DIGITAL UTILIZADO PELO LED
const int pinoLDR = 4; //PINO ANALÓGICO UTILIZADO PELO LDR
  
void setup(){  
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoLDR, INPUT); //DEFINE O PINO COMO ENTRADA
}    
void loop(){
  //O VALOR 600 PODE SER AJUSTADO
  if(analogRead(pinoLDR) > 600){ //SE O VALOR LIDO FOR MAIOR QUE 600, FAZ
    digitalWrite(pinoLed, HIGH); //ACENDE O LED
  }  
  else{ //SENÃO, FAZ
    digitalWrite(pinoLed, LOW); //APAGA O LED
  }  
}

WiFiServer server(80);
//CODIGO PRINCIPAL
void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); 
  pinMode(12, OUTPUT); //DEFINE O PINO COMO SAÍDA 
  pinMode(4, INPUT);
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
    client.print("<h1>RECEPCAO DE DADOS</h1>");
    client.print("<p>Informacoes da LED: </p>");
    if (led){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
    client.println("<li>A LED esta ligada</li>");
      }else{ 
        client.println("<li>A LED esta desligada!</li>");
      }
      client.print("<p>Informacoes do sensor de agua:</p>");
     if (agua){
      client.println("<li>A leitura do sensor e maior que 690 bits</li>");
      }else{
        client.print("<li>A leitura do sensor e menor que 690 bits ou sensor desligado!</li>");
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
