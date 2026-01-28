#include <Arduino.h>
#include "motori.h"


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Motore motore(PIN_MOT_AD1 , PIN_MOT_AD2,PIN_PWM_AD,PIN_ENC_AD1,PIN_ENC_AD2);
  motore.orario(200);
}

// the loop function runs over and over again forever
void loop() {
}