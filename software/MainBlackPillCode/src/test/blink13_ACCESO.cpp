#include <Arduino.h>
// il led builtin  è ACTIVE_LOW ..
#define ACCESO LOW
#define SPENTO HIGH
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,ACCESO);
}

// the loop function runs over and over again forever
void loop() {
  
}