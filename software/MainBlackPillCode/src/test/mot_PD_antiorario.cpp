#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN1_MOT_POS_DX , PIN2_MOT_POS_DX);
  motore.antiorario(200);
}

// the loop function runs over and over again forever
void loop() {
}
