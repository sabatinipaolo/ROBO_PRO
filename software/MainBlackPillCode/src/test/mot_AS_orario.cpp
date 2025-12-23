#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN_MOT_AS1 , PIN_MOT_AS2);
  motore.orario(200);
}

// the loop function runs over and over again forever
void loop() {
}