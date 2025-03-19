#include "settings.h"

void setFile(String fileName, String label, String value){
  File file = SPIFFS.open(fileName, "r");

  if (!file) {
    Serial.println("- failed to open config file for writing");
  }

  StaticJsonDocument<2040> doc;

  deserializeJson(doc, file);
  file.close();

  doc[label] = value;

  file = SPIFFS.open(fileName, "w");
  serializeJson(doc, file);
  file.close();
}

StaticJsonDocument<2040> getFile(String fileName){
  File file = SPIFFS.open(fileName, "r");

  if (!file) {
    Serial.println("- failed to open config file for writing");
  }

  StaticJsonDocument<2020> doc;

  deserializeJson(doc, file);
  file.close();

  return doc;
}
