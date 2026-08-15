#include <WiFi.h>
#include <WebServer.h>
#include <WiFiManager.h> // A biblioteca que acabamos de analisar

// Cria o servidor web na porta padrão (80)
WebServer server(80);

// Aqui criamos o visual do site (HTML) usando raw string literal (R"rawliteral(...)rawliteral")
// Isso permite escrever código HTML com aspas sem dar erro no C++
const char* html_page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Teste de Lógica ESP32</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; background-color: #f4f4f4;}
    input[type=text] { padding: 10px; width: 250px; border-radius: 5px; border: 1px solid #ccc;}
    input[type=submit] { padding: 10px 20px; cursor: pointer; background-color: #28a745; color: white; border: none; border-radius: 5px;}
  </style>
</head>
<body>
  <h2>Envie um texto para o Serial do ESP32</h2>
  <!-- O formulário envia os dados via método POST para o caminho "/enviar" -->
  <form action="/enviar" method="POST">
    <input type="text" name="mensagem" placeholder="Digite algo aqui..." required>
    <br><br>
    <input type="submit" value="Enviar para o ESP32">
  </form>
</body>
</html>
)rawliteral";

// Função que envia o HTML quando você acessa o IP principal
void handleRoot() {
  server.send(200, "text/html", html_page);
}

// Função que é ativada quando você aperta o botão "Enviar" no site
void handleForm() {
  // Verifica se o formulário realmente enviou o campo "mensagem"
  if (server.hasArg("mensagem")) {
    // Pega o texto digitado na caixa
    String textoRecebido = server.arg("mensagem"); 
    
    // Imprime no Monitor Serial
    Serial.println("=====================================");
    Serial.print("NOVA MENSAGEM RECEBIDA: ");
    Serial.println(textoRecebido);
    Serial.println("=====================================");

    // Redireciona o navegador de volta para a página principal para não ficar numa tela em branco
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    // Se der erro
    server.send(400, "text/plain", "Erro: Mensagem nao encontrada");
  }
}

void setup() {
  Serial.begin(115200);

  // Instancia o WiFiManager
  WiFiManager wifiManager;

  Serial.println("Iniciando WiFiManager...");
  wifiManager.resetSettings();
  // autoConnect cria um Access Point temporário chamado "ESP32_Config".
  // Se ele já tiver salvo a senha da sua casa, ele conecta direto e ignora o portal.
  if (!wifiManager.autoConnect("ESP32_Config")) {
    Serial.println("Falha ao conectar ou tempo limite atingido. Reiniciando...");
    delay(3000);
    ESP.restart(); // Reinicia o ESP se der erro
  }

  // Se o código chegou aqui, significa que o ESP32 conectou no seu Wi-Fi com sucesso!
  Serial.println("");
  Serial.println("Conectado ao Wi-Fi domiciliar!");
  Serial.print("Abra o navegador no celular/PC e digite este IP: ");
  Serial.println(WiFi.localIP());

  // Define as "rotas" do nosso servidor local
  server.on("/", HTTP_GET, handleRoot);       // Rota principal carrega o site
  server.on("/enviar", HTTP_POST, handleForm); // Rota "/enviar" recebe o texto do form

  // Inicia o servidor web local
  server.begin();
  Serial.println("Servidor Web iniciado e aguardando comandos.");
}

void loop() {
  // Mantém o servidor escutando se alguém entrou no site ou clicou no botão
  server.handleClient();
}
