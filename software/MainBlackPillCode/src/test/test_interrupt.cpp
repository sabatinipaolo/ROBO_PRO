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
//TO BE CONTINUED

}
