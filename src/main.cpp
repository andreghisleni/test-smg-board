#include <Arduino.h>

#define SDA_PIN 13
#define SCL_PIN 27

#define SOLENOIDE_PIN 32
#define SOLENOIDE_FALT 33


#define ADC_ADDR 0x50

/*
const int ledPinGreen = 21;
const int ledPinRed = 25;

#include <BQ25792_Driver.h>
#include <string.h>

#define SDA_PIN 32
#define SCL_PIN 27
#define STAT_LED 15

BQ25792 charger(0, 0);

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);

  analogWrite(ledPinGreen, 255);
  Serial.begin(115200);
  Serial.println("Hello World");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World 2");
  delay(1000);
  analogWrite(ledPinGreen, 0);
  analogWrite(ledPinRed, 255);
  delay(1000);
  analogWrite(ledPinGreen, 255);
  analogWrite(ledPinRed, 0);
  delay(1000);
  analogWrite(ledPinGreen, 127);
  analogWrite(ledPinRed, 127);
  delay(1000);
}*/

#include <string.h>
#include <Wire.h>
#include <BQ25792_Driver.h>
#include <ADC121C.h>


BQ25792 charger(0, 0);

ADC121C adc(ADC_ADDR);

const int ledPinGreen =  25;
const int ledPinRed = 21;
 
void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);

  analogWrite(ledPinGreen, 255);


  adc.begin(Wire);
  Serial.begin(115200);
  // start Charger
  charger.reset();
  delay(500);  // give the charger time to reboot

  pinMode(SOLENOIDE_PIN, OUTPUT);
  pinMode(SOLENOIDE_FALT, INPUT);

}
 
void loop() {



  digitalWrite(SOLENOIDE_PIN, HIGH);

  Serial.printf("Status: %s     Cells: %.1d     Max Voltage: %.5f     MinVoltage: %.1f     VBat: %.5f     Sensor: %.5f Solenoide Falt: %d \n",
   charger.getChargeStatus(), 
   charger.getCellCount(), 
   charger.getChargeVoltageLimit(), 
   charger.getVSYSMIN(), 
   charger.getVBAT(), 
   adc.readConversion(),
   digitalRead(SOLENOIDE_FALT)
  );

  if(digitalRead(SOLENOIDE_FALT)){
    analogWrite(ledPinGreen, 255);
  } else {

    analogWrite(ledPinRed, 255);
  }


  // Inicia a comunicação com o ADC
  Wire.beginTransmission(ADC_ADDR);
  Wire.write(0x00); // Endereço do registrador de resultado da conversão
  Wire.endTransmission();

  // Solicita os dados do ADC
  Wire.requestFrom(ADC_ADDR, 2); // Solicita 2 bytes de dados

  // Lê os bytes de dados e combina em um valor de 12 bits
  if (Wire.available() == 2) {
    uint8_t byteHigh = Wire.read();
    uint8_t byteLow = Wire.read();
    uint16_t adcValue = ((byteHigh << 8) | byteLow) >> 4; // Desloca 4 bits para a direita para obter o valor de 12 bits

    // Imprime o valor lido
    Serial.print("Valor do sensor: ");
    Serial.println(adcValue);
  } else {
    Serial.println("Erro ao ler do ADC.");
  }
  
  Serial.println(
   digitalRead(SOLENOIDE_FALT));
  
  delay(1000);
}