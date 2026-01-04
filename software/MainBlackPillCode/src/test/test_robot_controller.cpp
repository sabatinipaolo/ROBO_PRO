#include <Arduino.h>
#include "robot.h"
#include "controller.h"

Robot rob;
//Controller c(rob.motori);

void setup()
{
    rob.controller.motori[3].muovi(200);
}


void loop() 
{
}

