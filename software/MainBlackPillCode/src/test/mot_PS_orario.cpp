#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN_MOT_PS1 , PIN_MOT_PS2,PIN_PWM_PS,PIN_ENC_PS1,PIN_ENC_PS2);
  motore.orario(200);
}

// the loop function runs over and over again forever
void loop() {
}