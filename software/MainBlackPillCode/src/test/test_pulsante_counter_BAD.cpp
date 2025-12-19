/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-toggle-led
 */

#include <Arduino.h>

#define BUTTON_PIN PA8
// il led builtin  è ACTIVE_LOW ..
#define ACCESO LOW
#define SPENTO HIGH

int val = 0;

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, SPENTO);
  digitalWrite(BUTTON_PIN, LOW);
  Serial.begin(115200);
}

void loop()
{
  while (val <= 10)
    if (digitalRead(BUTTON_PIN) == HIGH)
    {
      digitalWrite(LED_BUILTIN, ACCESO);

      val++; // incrementa di 1 se il pulsante è premuto
      
      while (digitalRead(BUTTON_PIN) == HIGH)
      { } // attendi il rilascio del pulsante
      
      digitalWrite(LED_BUILTIN, SPENTO);

      //Serial.println(val);
    }

  Serial.println(val);
}