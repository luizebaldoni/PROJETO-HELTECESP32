#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <heltec.h>

// substitua os dados entre parênteses com o nome da Rede e a senha desejados
const char *ssid = "ESP32";
const char *password = "carrinho";

WiFiServer server(80);

//Confugurações dos pinos

int pinoLED = 12;

void setup() {
  
pinMode(pinoLED, INPUT);

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

WiFiClient client = server.available(); // verifica e armazena se tem clientes conectados na rede

if (client) { // se você conseguir um cliente,
Serial.println("Novo Cliente."); // imprime uma mensagem pela porta serial
String currentLine = ""; // faz uma String para manter os dados recebidos do cliente
while (client.connected()) { // loop enquanto o cliente está conectado
if (client.available()) { // se houver bytes para ler do cliente,
char c = client.read(); // leia um byte e depois
Serial.write(c); // imprima o monitor serial
if (c == '\n') { // se o byte for um caractere de nova linha


/* se a linha atual estiver em branco, você terá dois caracteres de nova linha em uma linha.
esse é o fim da solicitação HTTP do cliente, então envie uma resposta: */
if (currentLine.length() == 0) {
/* Os cabeçalhos HTTP sempre começam com um código de resposta (por exemplo, HTTP / 1.1 200 OK)
e um tipo de conteúdo para que o cliente saiba o que está por vir e, em seguida, uma linha em branco: */

client.println("HTTP/1.1 200 OK");
client.println  ("Content-type:text/html");
client.println();

client.print("<html>");
client.print("<head><title> ""Teste servidor"" </title></head>");
client.print("<body>");

// configuração de estilo do site
client.print("<style type=\"text/css\"> a{margin:600px 600px; background: #228B22; color: #ffffff; text-decoration: none; padding: 0.5% 5% 0.5%; border-radius: 5px; font-size: 2.0em;}</style>");

//---------------Botão liga para a página WEB----------------------
client.print("<a href=\"/FRENTE\">Liga</a> </br></br></br>");

//---------------Botão desliga para a página WEB----------------------
client.print("<a href=\"/VOLTAR\">Desliga</a> </br></br></br>");


client.print("</html>");
client.print("</body>");

// A resposta HTTP termina com outra linha em branco:
client.println();
// sair do loop while:
break;
} else { // se você tiver uma nova linha, então limpe a linha atual:
currentLine = "";
}
} else if (c != '\r') { // se você tiver qualquer outra coisa além de um caractere de retorno de linha,
currentLine += c; // adicioná-lo ao final da linha atual
}

// Verifica se o pedido do cliente foi para atualizar algum dos reles (GET /T)

if (currentLine.endsWith("GET /Liga")) {

digitalWrite(pinoLED, HIGH);

delay(100);

digitalWrite(pinoLED, LOW);
Serial.println("Liga");

}
if (currentLine.endsWith("GET /Desliga")) {

digitalWrite(pinoLED, LOW);
delay(100);

digitalWrite(pinoLED, LOW);

Serial.println("Desliga");

}

}
}
}
// termina a conexão com o cliente
client.stop();
//Serial.println("Cliente desconectado.");

}
