#include <Arduino.h>
#include "controller.h"

/// serve a loggare le rpm con pid o senza :
/// in platformio.ini ci sono i build flag per farlo ...


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
        Serial.println("Starting  =>  test_controller_stampa_RPM.cp.cpp");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(600);
        };

        Serial.println("Sarted  => test_controller_stampa_RPM.cp.cpp");
    }
    
    for (int i=0;i<4;i++){
        controller.motori[i].muovi(200);
    };

}

void loop()
{

    for (int i = 0; i < 4; i++)
    {
        Serial.print(" ");
        for (int im = 0; im < 4; im++)
        {
            Serial.print(controller.motori[im].get_rpm());
            Serial.print(" ");
        };
        Serial.println();
    }

    delay(100);
}