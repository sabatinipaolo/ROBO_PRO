#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN_MOT_PD1 , PIN_MOT_PD2,PIN_PWM_PD,PIN_ENC_PD1, PIN_ENC_PD2);
  motore.orario(200);
}

// the loop function runs over and over again forever
void loop() {
}