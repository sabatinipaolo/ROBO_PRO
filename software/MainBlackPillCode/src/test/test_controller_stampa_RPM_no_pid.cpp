#include <Arduino.h>


#define LOGGA_RPM 1

#include "controller.h"

void stampa_log( int indice_motore)
{   Motore &m=controller.motori[indice_motore];
    if (m.lettura_rpm_valida())
    {
        float rpm=m.get_rpm();
        float pwm=m.get_pwm();
        float pwm_base=m.get_pwm_base();

        Serial.print(" m.rpm = ");
        Serial.print(rpm);

        Serial.print(" / ");
        Serial.print(m._rpm_target);
        Serial.print(" topwm ");
        //Serial.print(target_to_pwm);
        
        Serial.print(" m.pwmbase = ");
        Serial.print(pwm_base);

        Serial.print(" m.pwm = ");
        Serial.print(pwm);

        Serial.print("outPID = ");
        Serial.print(controller.output_pids[indice_motore]);

        Serial.println();
    }
}

void setup()
{        



    controller.init();
    

    //no pid: non utilizzare controller.init_PID() o altro...



    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  =>  test_controller_stampa_RPM_no_pid");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(200);
        };
    }

    for (int i=0;i<4;i++){
    controller.motori[i].muovi(200);
    delay (22); // attende 1 o 2 misure
    }
}

void loop()
{
    // for (int i=0;i<4;i++){
    //     stampa_log(i);
    // };
    // Serial.println();

    // delay(1000);
    
}