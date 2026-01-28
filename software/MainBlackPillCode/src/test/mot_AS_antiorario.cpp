#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN_MOT_AS1, PIN_MOT_AS2,PIN_PWM_AS, PIN_ENC_AS1,PIN_ENC_AS2) ;
  motore.antiorario(200);
}

// the loop function runs over and over again forever
void loop() {
}
