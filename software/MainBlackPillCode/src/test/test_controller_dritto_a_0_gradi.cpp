#include <Arduino.h>
#include "controller.h"
float target=350;

void setup()
{    
    controller.init();
    Serial.begin(115200);

    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  =>   test_controller_RPM_e_PID");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(200);
        };
    }


    controller._mot_ant_dx.set_target_RPM(-target);
    controller._mot_pos_dx.set_target_RPM(-target);
    controller._mot_pos_sx.set_target_RPM(target);
    controller._mot_ant_sx.set_target_RPM(target);
    

    delay (22); // attende 1 o 2 misure
    
}

void loop()
{



    
}