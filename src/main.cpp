#include <Arduino.h>

const int ledPinGreen = 21;
const int ledPinRed = 25;

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
}