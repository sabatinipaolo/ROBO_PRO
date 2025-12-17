#include <Arduino.h>

#define PIN_INT PA8
// il led builtin  è ACTIVE_LOW ..
#define ACCESO LOW
#define SPENTO HIGH

void setup() {

    pinMode(PIN_INT, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    }

// the loop function runs over and over again forever
void loop() {
    int pinState = digitalRead(PIN_INT);
    digitalWrite(LED_BUILTIN, ! digitalRead(PIN_INT));
    // if (pinState  == HIGH) {
    //     digitalWrite(LED_BUILTIN, ACCESO);
    // } else {
    //     digitalWrite(LED_BUILTIN, SPENTO);
    // }
    
    //delay(500);  //se questo delay è alto il led è poco rispondente ...
                 // se è basso il led lampeggia in modo visibile ...

}
