#include "settings.h"

void inicialPins()
{
  // pinMode(resetButtonPin, INPUT_PULLUP);
  // pinMode(mq2_d, INPUT);
  // pinMode(mq2_a, INPUT);
  // pinMode(battery_a, INPUT);
  // pinMode(ledFogo, OUTPUT);
  // pinMode(ledWifi, OUTPUT);
  // pinMode(solenoide, OUTPUT);
  // digitalWrite(solenoide, sLOW);

  Wire.begin(SDA_PIN, SCL_PIN);

  // Configura o ADC para 12 bits (escreve 0x20 no registrador de configuração)
  Wire.beginTransmission(ADC_ADDR);
  Wire.write(0x02); // Endereço do registrador de configuração
  Wire.write(0x20); // Valor para habilitar o modo de 12 bits
  Wire.endTransmission();

  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);

  analogWrite(ledPinGreen, 255);
  analogWrite(ledPinRed, 0);

  // start Charger
  charger.reset();
  delay(500);  // give the charger time to reboot

  pinMode(SOLENOIDE_PIN, OUTPUT);
  pinMode(SOLENOIDE_FALT, INPUT);
}
void startSerial()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(250);
  }
}