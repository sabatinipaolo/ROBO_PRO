#include <Arduino.h>

void setup()
{
    Serial.begin(115200);

    while (!Serial){
        digitalWrite(LED_BUILTIN,HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN,LOW);
        delay(300);
    }
}

// the loop function runs over and over again forever
void loop()
{
    Serial.println(F("Hello, world!"));
    delay(2000);
}