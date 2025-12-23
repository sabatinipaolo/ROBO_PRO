#include <Arduino.h>
#include "motori.h"

  Motore mAD(PIN_MOT_AD1 , PIN_MOT_AD2);
  Motore mPD(PIN_MOT_PD1 , PIN_MOT_PD2);
  Motore mPS(PIN_MOT_PS1 , PIN_MOT_PS2);
  Motore mAS(PIN_MOT_AS1 , PIN_MOT_AS2);



void setup() {
  
  mAD.orario(200);
  mPD.orario(200);
  mPS.orario(200);
  mAS.orario(200);
  
    
}

// the loop function runs over and over again forever
void loop() {
}