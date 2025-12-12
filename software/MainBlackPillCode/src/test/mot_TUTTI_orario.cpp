#include <Arduino.h>
#include "motori.h"

  Motore mAD(PIN1_MOT_ANT_DX , PIN2_MOT_ANT_DX);
  Motore mPD(PIN1_MOT_POS_DX , PIN2_MOT_POS_DX);
  Motore mPS(PIN1_MOT_POS_SX , PIN2_MOT_POS_SX);
  Motore mAS(PIN1_MOT_ANT_SX , PIN2_MOT_ANT_SX);



void setup() {
  
  mAD.orario(200);
  mPD.orario(200);
  mPS.orario(200);
  mAS.orario(200);
  
    
}

// the loop function runs over and over again forever
void loop() {
}