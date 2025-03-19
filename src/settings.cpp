#include <Arduino.h>

#include <StreamUtils.h>

#include <ESPAsyncWebServer.h>

#include <WiFiClientSecure.h>

#include <ArduinoJson.h>

#include <Wire.h>

#include <BQ25792_Driver.h>

String url = "controller.monitoramentopreventivo.com.br";
// String url = "192.168.0.131";

String base_url = "http://" + url + "";
String mqtt_url = "38.242.235.60";
// uint16_t mqtt_port = 8683;
uint16_t mqtt_port = 1883;

String mac = "";
String key = "";

// WiFi
const char *ssid = "null";
const char *password = "null";

// MQTT
String controller_id = "";
String mqtt_user = "";
String mqtt_pass = "";

int buttonPin = 15; // TODO: verificar o pino do botão

int ledPinGreen = 25;
int ledPinRed = 21;

BQ25792 charger(0, 0);

int SDA_PIN = 13;
int SCL_PIN = 27;

int SOLENOIDE_PIN = 32;
int SOLENOIDE_FALT = 33;
int ADC_ADDR = 0x50;

// int solenoide = 21; // pino do rele da solenoide

// int mq2_d = 34;         // pino digital sensor de gas
// int mq2_a = 35;         // pino analogico sensor de gas
// int mq2_a_value = 1000; // valor para detecção do vasamento

// int battery_a = 33; // pino analogico da bateria


// // variaveis utilizadas na aplicação em escopo global

bool gasblok = false;
bool bloqueado = false;

int timerr = 0;

bool offline = false;
int timerOffline = 0;

EepromStream saveHitory(126, 125);

boolean connected = false;

AsyncWebServer server(3872);

StaticJsonDocument<200> settingsData;

const char *generateUID();

boolean needConfiguration = true;

String token = "";

String code_version = "1.0.0";