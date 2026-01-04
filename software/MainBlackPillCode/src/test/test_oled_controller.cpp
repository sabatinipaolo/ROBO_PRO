#include <Arduino.h>
#include "controller.h"
#include "oled.h"


void setup()
{   controller.init();
    oled.begin();
}

void loop()
{
    controller._mot_ant_dx.set_target_RPM(400);
    controller._mot_pos_dx.set_target_RPM(400);
    controller._mot_pos_sx.set_target_RPM(400);
    controller._mot_ant_sx.set_target_RPM(400);

    oled.stampa4rpm(controller);
    
}
