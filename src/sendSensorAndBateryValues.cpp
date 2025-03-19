#include "settings.h"

extern PubSubClient mqtt_client;
extern String statusSensorsTopic;
extern String onlineTopic;

void sendSensorAndBateryValues()
{

  int batteryLevelReading = analogRead(battery_a);

  float batteryLevel = batteryLevelReading * float(14) / float(4095);

  Serial.print("Battery Level: ");
  Serial.println(batteryLevel);

  String message = "{\"sensorValue\": \"" + String(analogRead(mq2_a)) + "\",\"batteryLevel\": \"" + String(batteryLevel) + "\"}";

  Serial.println(message);

  mqtt_client.publish(statusSensorsTopic.c_str(), message.c_str());
  mqtt_client.publish(onlineTopic.c_str(), "");

  delay(5000);
}
