#include "settings.h"

void sendOldLeituras()
{

  StaticJsonDocument<200> arquivo;

  File file = SPIFFS.open("/disparos.json", "r");

  if (!file)
  {
    Serial.println("- failed to open config file");
  }

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, file);
  serializeJson(doc, Serial);
  Serial.println();
  file.close();

  JsonArray array = doc.as<JsonArray>();
  Serial.println(doc.as<String>());

  // StaticJsonDocument<200> response = httpPostRequest(array);

  // serializeJson(response, Serial);

  file = SPIFFS.open("/disparos.json", "w");

  if (!file)
  {
    Serial.println("- failed to open config file");
  }

  DynamicJsonDocument doc2(2048);
  deserializeJson(doc2, "[]");
  serializeJson(doc2, file);
  serializeJson(doc2, Serial);
  Serial.println();
  file.close();
}
