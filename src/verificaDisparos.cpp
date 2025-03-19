#include "settings.h"

extern PubSubClient mqtt_client;
extern String bockTopic;

void verificaddisparo()
{
  digitalWrite(2, digitalRead(mq2_d));
  if (digitalRead(mq2_d) != HIGH && analogRead(mq2_a) > mq2_a_value && !gasblok)
  {
    Serial.println("-------------------------------------------------------");
    Serial.println("Fogo");
    gasblok = true;
    digitalWrite(ledFogo, HIGH);

    mqtt_client.publish(bockTopic.c_str(), "");

    Serial.println("Fogo detectado");

    delay(1000);
    Serial.println("-------------------------------------------------------");
  }
}
