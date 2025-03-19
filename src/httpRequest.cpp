#include "settings.h"

void wifiError(int code);

boolean httpPostRequestFirstConnection()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    wifiError(9999);
    Serial.println(WiFi.status());
  }
  else
  {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    if (http.begin(base_url + "/controllers/fisrt-connection"))
    {

      Serial.print("[HTTP] POST...\n");
      http.addHeader("Content-Type", "application/json");

      String serializedJson = "";

      StaticJsonDocument<1000> requastBody;

      requastBody["macAddress"] = mac;
      requastBody["code_version"] = code_version;
      requastBody["ssid"] = WiFi.SSID();
      requastBody["ip"] = WiFi.localIP().toString();

      serializeJson(requastBody, serializedJson);

      Serial.println(serializedJson);

      int httpCode = http.POST(serializedJson);

      // httpCode will be negative on error
      if (httpCode > 0)
      {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          String body = http.getString();
          Serial.println("body" + body);
          wifiError(httpCode);

          StaticJsonDocument<300> doc;
          deserializeJson(doc, body);
          serializeJson(doc, Serial);
          Serial.println();

          if (doc["mqtt_connect"].as<boolean>() == true)
          {
            controller_id = doc["id"].as<String>();
            mqtt_user = mac;
            mqtt_pass = doc["key"].as<String>();

            boolean blocked = doc["blocked"].as<boolean>();

            Serial.println(blocked);
            if (blocked and !gasblok)
            {
              Serial.println("Gás Bloqueado");
              gasblok = true;
            }
            else if (!blocked and gasblok)
            {
              Serial.println("Gás Aberto");
              gasblok = false;
            }
            return true;
          }
        }
        else
        {
          wifiError(httpCode);
        }
      }
      else
      {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    else
    {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  return false;
}

void wifiError(int code)
{
  if (code == 200)
  {
    offline = false;
  }
  if (code != 200)
  {
    // digitalWrite(ledWifi, HIGH);
    analogWrite(ledPinRed, 0);
    analogWrite(ledPinGreen, 0);
    Serial.println("Erro de Wifi");
    offline = true;
  }
  if (code == 9999)
  {
    WiFi.reconnect();
    offline = true;
  }
}
