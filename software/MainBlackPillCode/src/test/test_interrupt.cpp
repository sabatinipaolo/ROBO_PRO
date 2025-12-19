#include <Arduino.h>

#define BUTTON_PIN PB15
// il led builtin  è ACTIVE_LOW ..
#define ACCESO LOW
#define SPENTO HIGH

const int timeThreshold = 10;


volatile int val = 0;

int numero_pressioni = 0;
long startTime = 0;

bool stato_led;


void ISR_rising()
{
  if (millis() - startTime > timeThreshold)
  { Serial.println("rising");
    digitalWrite(LED_BUILTIN,ACCESO);
    val++;
    startTime = millis();

  }
  Serial.println("rising");
}
void ISR_falling()
{
  if (millis() - startTime > timeThreshold)
  { Serial.println("rising");
    digitalWrite(LED_BUILTIN,SPENTO);
    startTime = millis();

  }
}


void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,SPENTO);

  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR_rising, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR_falling, FALLING);

}

void loop()
{
  if (numero_pressioni != val)
  {
    numero_pressioni = val;
    digitalWrite(LED_BUILTIN,ACCESO);
    Serial.println(numero_pressioni);

  }
  digitalWrite(LED_BUILTIN,SPENTO);

}



