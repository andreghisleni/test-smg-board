
#include "settings.h"

extern void verificaddisparo();
extern void sendOldLeituras();
extern void setupMQTT();
extern void startMqttLoop();

void inicialPins();
void startSerial();
void startWifi();
void setLoops();

int estadoBotao = 0;
unsigned long tempoInicio = 0;
bool botaoPressionado = false;

void setup()
{
  inicialPins();

  startSerial();

  SPIFFS.begin(true);

  // if (digitalRead(buttonPin) == LOW)
  // {
  //   Serial.println("Resetando configurações");
  //   SPIFFS.format();
  //   Serial.println("Reiniciando em 15 segundos");
  //   delay(15000);
  //   ESP.restart();
  // }

  tempoInicio = millis(); // Registra o tempo de início

  while (millis() - tempoInicio < 5000) { // Verifica por 5 segundos
    analogWrite(ledPinGreen, 0); // Liga o LED verde
    analogWrite(ledPinRed, 255); // Desliga o LED vermelho
    estadoBotao = digitalRead(buttonPin);
    if (estadoBotao == LOW) { // Botão pressionado
      botaoPressionado = true; // Marca que o botão foi pressionado
    }
    delay(10); // Pequeno delay para evitar leituras muito rápidas
  }

  if (botaoPressionado) {
    Serial.println("Botão pressionado durante a inicialização!");
    // Coloque aqui a ação desejada
    analogWrite(ledPinGreen, 255); // Desliga o LED verde
    analogWrite(ledPinRed, 0); // Liga o LED vermelho
    Serial.println("Resetando configurações");
    SPIFFS.format();
    Serial.println("Reiniciando em 15 segundos");
    delay(5000);
    analogWrite(ledPinGreen, 130); // Desliga o LED verde
    analogWrite(ledPinRed, 130); // Liga o LED vermelho
    delay(5000);
    analogWrite(ledPinGreen, 0); // Desliga o LED verde
    analogWrite(ledPinRed, 0); // Liga o LED vermelho
    delay(5000);
    analogWrite(ledPinGreen, 130); // Desliga o LED verde
    analogWrite(ledPinRed, 130); // Liga o LED vermelho
    ESP.restart();
  } else {
    Serial.println("Botão não pressionado durante a inicialização.");
  }

  Serial.println("Inicialização concluída."); // Mensagem de fim da verificação

  // pinMode(2, OUTPUT);
  // digitalWrite(2, HIGH);
  // delay(5000);
  // digitalWrite(2, LOW);

  Serial.println("Iniciando");

  // setFile("/settings.json", "SSID", "null");
  // setFile("/settings.json", "WIFI_PASS", "null");

  settingsData = getFile("/settings.json");

  startWifi();

  if (!needConfiguration)
  {
    // sendOldLeituras();

    delay(1000);

    Serial.println("Iniciado");

    // StaticJsonDocument<200> response = httpPostRequest("Vazamento", 0);

    // serializeJson(response, Serial);

    // delay(1000);

    boolean goToNextStep = httpPostRequestFirstConnection();

    if (!goToNextStep)
    {

      Serial.println("Erro ao conectar com o servidor, controladora não configurada");
      Serial.println("Reiniciando em 15 segundos");

      delay(15000);

      ESP.restart();
    }

    Serial.println("Conectado com o servidor");

    analogWrite(ledPinGreen, 255);
    analogWrite(ledPinRed, 0);

    // connect to mqtt
    setupMQTT();
    startMqttLoop();

    // verificaddisparo();

    delay(2000);

    setLoops();
  }
}

void loop()
{
  LoopWifi();
}
