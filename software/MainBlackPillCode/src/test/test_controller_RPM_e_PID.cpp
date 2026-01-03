#include <Arduino.h>
#include "controller.h"
    


Motore &m = controller._mot_pos_sx;
float target=350;


void setup()
{    
    controller.init();
    controller.disable_PID();

    Serial.begin(115200);

    // { // starting serial e programma
    //     Serial.begin(115200);
    //     while (!Serial1)
    //         ;
    //     Serial.println("Starting  =>   test_controller_RPM_e_PID");

    //     for (int i = 10; i > 0; i--)
    //     {
    //         Serial.print("inizio tra ");
    //         Serial.println(i);
    //         delay(200);
    //     };
    // }

    
    m.set_target_RPM(target);

}

void loop()
{
    if (m.lettura_rpm_valida())
    {
        Serial.print(target);
        Serial.print("/");
        Serial.print(m.get_rpm());
        Serial.println();
    }
    
    
}