#include "settings.h"

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

extern void topic1Select(JsonObject obj);

// variaveis que indicam o núcleo
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne = 1;

long lastMsg = 0;
char msg[50];
int value = 0;

String topic1_part1 = "/controller/";
String topic1_part2 = "/user-update-status";
String topic2_part1 = "/update/";
String topic1 = "";
String topic2 = "";
String willTopic = "";
String bockTopic = "";
String statusSensorsTopic = "";
String onlineTopic = "";
String updatingTopic = "";
String restartingTopic = "";

void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
void setupMQTT();

void setupMQTT()
{
  topic1 = topic1_part1 + controller_id + topic1_part2;
  willTopic = topic1_part1 + controller_id + "/offline";
  bockTopic = topic1_part1 + controller_id + "/block";
  statusSensorsTopic = topic1_part1 + controller_id + "/status-sensors";
  onlineTopic = topic1_part1 + controller_id + "/online";
  updatingTopic = topic1_part1 + controller_id + "/updating";
  restartingTopic = topic1_part1 + controller_id + "/restarting";

  topic2 = topic2_part1 + controller_id;

  Serial.println("setupMQTT");

  mqtt_client.setServer(mqtt_url.c_str(), mqtt_port);
  mqtt_client.setCallback(callback);
}
void callback(char *topic, byte *payload, unsigned int length)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);
  JsonObject obj = doc.as<JsonObject>();
  if (strcmp(topic, topic1.c_str()) == 0)
  {
    topic1Select(obj);
  }
  else if (strcmp(topic, topic2.c_str()) == 0)
  {
    Serial.println("update");
    // update(obj["url"].as<String>(), 80);
    Serial.println("update");
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!mqtt_client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random mqtt_client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqtt_client.connect(clientId.c_str(), mqtt_user.c_str(), mqtt_pass.c_str(), willTopic.c_str(), 0, true, "{\"turnoff\": true}"))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...

      StaticJsonDocument<200> doc;

      doc["text"] = "portao RFID";

      char buffer[512];
      serializeJson(doc, buffer);
      mqtt_client.publish("outTopic", buffer);

      // ... and resubscribe
      Serial.println(topic1);
      mqtt_client.subscribe(topic1.c_str());
      mqtt_client.subscribe(topic2.c_str());

      // digitalWrite(ledWifi, LOW);
      analogWrite(ledPinRed, 0);
      analogWrite(ledPinGreen, 0);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      // digitalWrite(ledWifi, HIGH);
      analogWrite(ledPinRed, 100);
      analogWrite(ledPinGreen, 180);
      delay(5000);
    }
  }
}

void loopMQTT()
{
  if (!mqtt_client.connected())
  {
    reconnect();
    delay(1000);
  }
  mqtt_client.loop();
}

void mqttLoopRun(void *pvParameters)
{
  while (true)
  {
    loopMQTT();
  }
}

void startMqttLoop()
{

  xTaskCreatePinnedToCore(mqttLoopRun, "mqttLoopRun", 10000, NULL, 1, NULL, taskCoreOne);
  delay(2000);

  Serial.println("mqttLoopRun task started");
  delay(1000);
}