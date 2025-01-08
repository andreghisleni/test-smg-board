#include <Arduino.h>

#define SDA_PIN 13
#define SCL_PIN 27

#define SOLENOIDE_PIN 32

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

ADC121C adc(0x50);
 
void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);


  adc.begin(Wire);
  Serial.begin(115200);
  // start Charger
  charger.reset();
  delay(500);  // give the charger time to reboot

  pinMode(SOLENOIDE_PIN, OUTPUT);

  digitalWrite(SOLENOIDE_PIN, LOW);

}
 
void loop() {
  Serial.printf("Status: %s     Cells: %.1d     Max Voltage: %.5f     MinVoltage: %.1f     VBat: %.5f     Sensor: %.5f \n",
   charger.getChargeStatus(), 
   charger.getCellCount(), 
   charger.getChargeVoltageLimit(), 
   charger.getVSYSMIN(), 
   charger.getVBAT(), 
   adc.readConversion()
  );
  
  
  delay(1000);
}