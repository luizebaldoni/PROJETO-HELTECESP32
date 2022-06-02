#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "ESP32";
const char *password = "Teste03";
//DEFINICOES
const int pinosensor = 4;       // Pino conectado ao sensor
const int pinoLED = 12; // Pino conectado à LED
WiFiServer server(80);
//CODIGO PRINCIPAL
void setup() {
  Serial.begin(115200); //Inicia comunicação serial
  Serial.println();
  Serial.println("configurando...");    
  delay(6000); // Aguarda o sensor armar       
  pinMode(pinosensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA    
  WiFi.softAP(ssid, password); // DEFINE que para ter acesso precisa senha
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("O Endereço IP Da Rede : ");
  Serial.println(myIP);
  server.begin(); //inicia o webserver
  Serial.println("Servidor Iniciado!!");


}
//CONDICOES
void loop() {
  if(analogRead(pinosensor) > 690){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      printf("A leitura do sensor é amior q 690 bits"); //ACENDE O LED
  }else{ //SENÃO, EXECUTA:
    digitalWrite(pinoLED, LOW); //DESLIGA O LED
  }
  WiFiClient client = server.available(); 
  if (client) { // se você conseguir um cliente,
  Serial.println("Novo Cliente."); // imprime uma mensagem pela porta serial
  String currentLine = ""; // faz uma String para manter os dados recebidos do cliente
  while (client.connected()) { // loop enquanto o cliente está conectado
  if (client.available()) { // se houver bytes para ler do cliente,
  char c = client.read(); // leia um byte e depois
  Serial.write(c); // imprima o monitor serial
  if (c == '\n') { // se o byte for um caractere de nova linha
  if (currentLine.length() == 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html>");
    client.println("<head><meta http-equiv='refresh' content='1'><tittle>Servidor ESP32</tittle></head>");
    client.println("<h1>Recebendo dados da porta analogica</h1>");
    client.println("<p>Valor da porta analógica:</p>");
    if (analogRead(pinosensor) > 690){ //SE A LEITURA DO PINO FOR MAIOR QUE 690 BITS (PODE SER AJUSTADO), EXECUTA:
      client.println("<p>A leitura do sensor é maior q 690 bits</p>");
      }else if (analogRead(pinosensor) < 690){ 
        client.println("<p>A leitura do sensor é menor do que a esperada</p>"); 
      }else{ 
        client.println("<p>Nao foi possivel ler o sensor!</p>");
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
