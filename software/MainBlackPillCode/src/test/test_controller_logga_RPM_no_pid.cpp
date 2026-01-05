#include <Arduino.h>
#include "controller.h"

void stampa_rpm_da_loop( int indice_motore)
{   Motore &m=controller.motori[indice_motore];

    {
        float rpm=m.get_rpm();
        float pwm=m.get_pwm();
        float pwm_base=m.get_pwm_base();
        Serial.print(" motore n. = ");
        Serial.print(indice_motore);

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

unsigned long int ora_start=0;
void setup()
{        

    controller.init();


    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  =>  test_controller_stampa_RPM_no_pid");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(1000);
        };
    }
ora_start=millis();
    for (int i=0;i<4;i++){
        //controller.motori[i].indice_log_RPM=0; //resetta la log ..
        controller.motori[i].muovi(-200);
    };


}

void loop()
{

    if ((millis()-ora_start ) <= 3000){
    //if (0){
        for (int i=0;i<4;i++)
            stampa_rpm_da_loop(i);
        Serial.println();
        delay(100);
    }
    else
    {

controller.stampa_log_RPM_4_motori();
delay(3000);


        
    }
}