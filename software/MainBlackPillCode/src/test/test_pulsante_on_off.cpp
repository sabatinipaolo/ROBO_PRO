#include <Arduino.h>

#define BUTTON_PIN PA8
// il led builtin  è ACTIVE_LOW ..
#define ACCESO LOW
#define SPENTO HIGH

void setup() {

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, SPENTO);
    Serial.begin(115200);

}

// the loop function runs over and over again forever
void loop() {
    int pinState = digitalRead(BUTTON_PIN);
    digitalWrite(LED_BUILTIN, not pinState);
    
    // 
    // if (pinState  == HIGH) {
    //     digitalWrite(LED_BUILTIN, ACCESO);
    // } else {
    //     digitalWrite(LED_BUILTIN, SPENTO);
    // }
    Serial.println(pinState);
    //delay(500);  //se questo delay è alto il led è poco rispondente ...
                 // se è basso il led lampeggia in modo visibile ...

}
