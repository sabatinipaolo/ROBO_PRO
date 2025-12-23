#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN_MOT_PS1 , PIN_MOT_PS2);
  motore.antiorario(200);
}

// the loop function runs over and over again forever
void loop() {
}
