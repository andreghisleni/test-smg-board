#include "settings.h"

void topic1Select(JsonObject obj);
void topic1Loop();

boolean blocked;

void topic1Select(JsonObject obj)
{

  serializeJson(obj, Serial);

  // code = obj["code"].as<int>();
  blocked = obj["blocked"].as<boolean>();

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
}

void topic1Loop()
{
}
