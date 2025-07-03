#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Substitua com suas credenciais
const char* ssid = "NOME DO SEU WIFI";
const char* password = "SENHA DO SEU WIFI";
const char* botToken = "SEU TOKEN";
const char* chatID = "SEU ID DO CHAT";

// Pinos dos LDRs e do buzzer
const int ldr1 = 34;
const int ldr2 = 35;
const int ldr3 = 32;
const int buzzerPin = 33;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(botToken, secured_client);

bool alarmeAtivado = false;
int limiar = 1000; // Ajuste este valor conforme a luz ambiente

void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  // Conectando-se ao Wi-Fi
  WiFi.begin(ssid, password);
  secured_client.setInsecure(); // Ignora certificado SSL
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi!");
  bot.sendMessage(chatID, "Sistema de segurança a laser iniciado.", "");
}

void loop() {
  int valor1 = analogRead(ldr1);
  int valor2 = analogRead(ldr2);
  int valor3 = analogRead(ldr3);

  Serial.print("LDR1: "); Serial.print(valor1);
  Serial.print(" | LDR2: "); Serial.print(valor2);
  Serial.print(" | LDR3: "); Serial.println(valor3);

  bool feixe1 = valor1 > limiar;
  bool feixe2 = valor2 > limiar;
  bool feixe3 = valor3 > limiar;

  int rompidos = feixe1 + feixe2 + feixe3;

  if (rompidos == 3 && !alarmeAtivado) {
    bot.sendMessage(chatID, "🚨 Todos os 3 feixes foram rompidos!", "");
    tone(buzzerPin, 1000); // Toca som contínuo
    alarmeAtivado = true;
  }

  // Envia alertas parciais também
  if ((rompidos == 1 || rompidos == 2) && !alarmeAtivado) {
    String msg = "⚠️ Feixes rompidos: " + String(rompidos);
    bot.sendMessage(chatID, msg, "");
  }

  // Se os feixes forem restaurados, resetar alarme
  if (rompidos < 3 && alarmeAtivado) {
    bot.sendMessage(chatID, "✅ Feixes restaurados. Sistema rearmado.", "");
    noTone(buzzerPin); // Para som
    alarmeAtivado = false;
  }

  delay(1000);
}
