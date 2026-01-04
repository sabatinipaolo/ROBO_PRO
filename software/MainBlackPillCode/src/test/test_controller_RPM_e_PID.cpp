#include <Arduino.h>
#include "controller.h"
float target=400;

//per test usiano la curva uguale per tutti i motori
float target_to_pwm=controller._mot_ant_dx.rpm_to_pwm(target);    



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
        Serial.print(target_to_pwm);
        
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
    controller.disable_PID();

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

    for (int i=0;i<4;i++){
    controller.motori[i].set_target_RPM(target);
    delay (22); // attende 1 o 2 misure
    }
}

void loop()
{
    for (int i=0;i<4;i++){
        stampa_log(i);
    };
    Serial.println();

    delay(1000);
    
}