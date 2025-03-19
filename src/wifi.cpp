#include "settings.h"

void startWifi()
{
  WiFi.disconnect(true);
  delay(1000);

  if ((settingsData["SSID"].as<String>() != "null" && settingsData["WIFI_PASS"].as<String>() != "null") || (ssid != "null" && password != "null"))
  {
    if (ssid != "null" && password != "null")
    {
      WiFi.begin(ssid, password);
    }
    else
    {
      WiFi.begin(settingsData["SSID"].as<String>().c_str(), settingsData["WIFI_PASS"].as<String>().c_str());
    }

    needConfiguration = false;

    Serial.print("Connecting... ");

    int verifyTime = 0;

    char later[1];

    while (WiFi.status() != WL_CONNECTED && verifyTime != 60)
    {
      Serial.print('.');

      if (Serial.available() > 0)
      {
        Serial.readBytes(later, 1);
        if (later[0] == 'r')
        {
          setFile("/settings.json", "SSID", "null");
          setFile("/settings.json", "WIFI_PASS", "null");

          ESP.restart();
        }
      }

      delay(1000);
      verifyTime++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("SSID: ");
      Serial.println(WiFi.SSID());
      Serial.println("MAC: ");
      Serial.println(WiFi.macAddress());

      mac = WiFi.macAddress();

      connected = true;
    }
    else
    {
      Serial.println("Time: " + String(verifyTime));
      connected = false;
    }
  }
  else
  {

    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    Serial.println("Please connect to the AP");
  }

  server.addHandler(new AsyncCallbackJsonWebHandler("/reset", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                    {
                                                      if (!request->hasHeader("token") || !token)
                                                      {
                                                        return request->send(401);
                                                      }
                                                      AsyncWebHeader *hToken = request->getHeader("token");

                                                      if (String(hToken->value().c_str()) != token)
                                                      {
                                                        return request->send(401);
                                                      }

                                                      // SPIFFS.remove("/settings.json");
                                                      setFile("/settings.json", "SSID", "null");
                                                      setFile("/settings.json", "WIFI_PASS", "null");

                                                      StaticJsonDocument<200> jsonBuffer;
                                                      jsonBuffer["message"] = "Dados excluidos com sucesso";

                                                      String response;

                                                      serializeJson(jsonBuffer, response);

                                                      request->send(200, "application/json", response); }));

  server.addHandler(new AsyncCallbackJsonWebHandler("/setData", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                    {
                                                      if (!request->hasHeader("token") || !token)
                                                      {
                                                        return request->send(401);
                                                      }
                                                      AsyncWebHeader *hToken = request->getHeader("token");

                                                      if (String(hToken->value().c_str()) != token)
                                                      {
                                                        return request->send(401);
                                                      }

                                                      if (json["SSID"].as<String>() == "null")
                                                      {
                                                        StaticJsonDocument<200> jsonBuffer;
                                                        jsonBuffer["message"] = "SSID é necessario";

                                                        String response;

                                                        serializeJson(jsonBuffer, response);

                                                        return request->send(200, "application/json", response);
                                                      }
                                                      if (json["WIFI_PASS"].as<String>() == "null")
                                                      {
                                                        StaticJsonDocument<200> jsonBuffer;
                                                        jsonBuffer["message"] = "Password é necessario";

                                                        String response;

                                                        serializeJson(jsonBuffer, response);

                                                        return request->send(200, "application/json", response);
                                                      }

                                                      // SPIFFS.remove("/settings.json");
                                                      setFile("/settings.json", "SSID", json["SSID"].as<String>());
                                                      setFile("/settings.json", "WIFI_PASS", json["WIFI_PASS"].as<String>());

                                                      StaticJsonDocument<200> jsonBuffer;
                                                      jsonBuffer["message"] = "Dados auterados com sucesso";
                                                      jsonBuffer["r"] = json;

                                                      String response;

                                                      serializeJson(jsonBuffer, response);

                                                      request->send(200, "application/json", response); }));

  server.addHandler(new AsyncCallbackJsonWebHandler("/wifi", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                    {
                                                      if (!request->hasHeader("token") || !token)
                                                      {
                                                        return request->send(401);
                                                      }
                                                      AsyncWebHeader *hToken = request->getHeader("token");

                                                      if (String(hToken->value().c_str()) != token)
                                                      {
                                                        return request->send(401);
                                                      }

                                                      StaticJsonDocument<200> jsonBuffer;
                                                      jsonBuffer["heap"] = ESP.getFreeHeap();
                                                      jsonBuffer["ssid"] = WiFi.SSID();
                                                      jsonBuffer["data"] = getFile("/settings.json");

                                                      String response;

                                                      serializeJson(jsonBuffer, response);

                                                      request->send(200, "application/json", response); }));

  server.addHandler(new AsyncCallbackJsonWebHandler("/login", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                    {
                                                      if (json["user"].as<String>() == "null" || json["pass"].as<String>() == "null")
                                                      {
                                                        return request->send(401);
                                                      }

                                                      String HUser = json["user"].as<String>();
                                                      String HPass = json["pass"].as<String>();

                                                      StaticJsonDocument<200> jsonBuffer;

                                                      
                                                      if (HUser == "admin" && HPass == "admin")
                                                      {
                                                        token = generateUID();

                                                        jsonBuffer["token"] = token;
                                                      }
                                                      else
                                                      {
                                                        return request->send(401);
                                                      }
                                                      

                                                      String response;

                                                      serializeJson(jsonBuffer, response);

                                                      request->send(200, "application/json", response); }));

  server.addHandler(new AsyncCallbackJsonWebHandler("/reload", [](AsyncWebServerRequest *request, JsonVariant &json)
                                                    {
                                                      if (!request->hasHeader("token") || !token)
                                                      {
                                                        return request->send(401);
                                                      }
                                                      AsyncWebHeader *hToken = request->getHeader("token");

                                                      if (String(hToken->value().c_str()) != token)
                                                      {
                                                        return request->send(401);
                                                      }

                                                      StaticJsonDocument<200> jsonBuffer;
                                                      jsonBuffer["message"] = "esp is reloading";

                                                      String response;

                                                      serializeJson(jsonBuffer, response);

                                                      request->send(200, "application/json", response);

                                                      ESP.restart(); }));

  server.onNotFound([](AsyncWebServerRequest *request)
                    { request->send(404); });

  server.begin();
}

unsigned long previous_time = 0;
unsigned long d = 30000;

void LoopWifi()
{
  unsigned long current_time = millis(); // number of milliseconds since the upload

  // checking for WIFI connection
  if ((WiFi.status() != WL_CONNECTED) && (current_time - previous_time >= d))
  {
    Serial.print(millis());
    Serial.println("Reconnecting to WIFI network");
    WiFi.disconnect();
    WiFi.reconnect();
    previous_time = current_time;
  }
}
