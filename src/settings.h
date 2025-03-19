#include <Arduino.h>

#include <WiFi.h>

#include <WiFiClientSecure.h>

#include <HTTPClient.h>

#include <ArduinoJson.h>

#include <SPIFFS.h>

#include <StreamUtils.h>

#include <ESPAsyncWebServer.h>

#include <AsyncJson.h>

#include <PubSubClient.h>

#include <Wire.h>

#include <BQ25792_Driver.h>

extern String base_url;
extern String mqtt_url;
extern uint16_t mqtt_port;

extern String mac;
extern String key;

extern String controller_id;
extern String mqtt_user;
extern String mqtt_pass;

extern int buttonPin;

extern int ledPinGreen;
extern int ledPinRed;

extern BQ25792 charger;

extern int SDA_PIN;
extern int SCL_PIN;

extern int SOLENOIDE_PIN;
extern int SOLENOIDE_FALT;
extern int ADC_ADDR;

// extern int solenoide;

// extern int mq2_d;
// extern int mq2_a;
// extern int mq2_a_value;

// extern int battery_a;

// extern int sHIGH;
// extern int sLOW;

// // variaveis utilizadas na aplicação em escopo global

extern bool gasblok;
extern bool bloqueado;

extern int timerr;

extern bool offline;
extern int timerOffline;

extern EepromStream saveHitory;

extern boolean connected;

extern char *ssid;
extern char *password;

extern AsyncWebServer server;

extern void LoopWifi();

extern void setFile(String fileName, String label, String value);
extern StaticJsonDocument<2040> getFile(String fileName);

extern StaticJsonDocument<200> settingsData;

extern const char *generateUID();

extern boolean httpPostRequestFirstConnection();

extern boolean needConfiguration;

extern String token;

extern void update(String url, int port);

extern String code_version;