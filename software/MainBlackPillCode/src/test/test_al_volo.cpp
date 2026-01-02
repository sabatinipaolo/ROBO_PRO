#include <Arduino.h>
#include "controller.h"

#define LOGGA_RPM
Controller c;

unsigned long int time_inizio = millis();
void setup()
{

    Serial.begin(115200);

    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting program ");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio misura tra ");
            Serial.println(i);
            delay(333);
        };
    }

    Serial.println("accendo motori ");

    float target = 330;
    c._mot_ant_dx._rpm_target = target;
    //c._mot_ant_dx.muovi(c._mot_ant_dx.rpm_to_pwm(target));
    c._mot_ant_dx.muovi(255);

    c._mot_pos_dx._rpm_target = target;
    c._mot_pos_dx.muovi(c._mot_pos_dx.rpm_to_pwm(target));

    c._mot_pos_sx._rpm_target = target;
    c._mot_pos_sx.muovi(c._mot_pos_sx.rpm_to_pwm(target));

    c._mot_ant_sx._rpm_target = target;
    c._mot_ant_sx.muovi(c._mot_ant_sx.rpm_to_pwm(target));

   // while ((millis() - time_inizio) < 10000)
    while (1)
    {
        {//stampa sit.
            
            Serial.print(" ");
            Serial.print(c._mot_ant_dx._rpm_target);
            Serial.print("/");
            Serial.print(c._mot_ant_dx._rpm);
            Serial.print(" pwm= ");
            Serial.print(c._mot_ant_dx._pwm);
            Serial.print(" outPID =");
            Serial.print(c.output_pid_AD);

            // Serial.print(" ");
            // Serial.print(c._mot_pos_dx._rpm_target);
            // Serial.print("/");
            // Serial.print(c._mot_pos_dx._rpm);
            // Serial.print(" pwm= ");
            // Serial.print(c._mot_pos_dx._pwm);
            // Serial.print(" outPID =");
            // Serial.print(c.output_pid_PD);

            // Serial.print(" ");
            // Serial.print(c._mot_pos_sx._rpm_target);
            // Serial.print("/");
            // Serial.print(c._mot_pos_sx._rpm);
            // Serial.print(" pwm= ");
            // Serial.print(c._mot_pos_sx._pwm);
            // Serial.print(" outPID =");
            // Serial.print(c.output_pid_PS);

            // Serial.print(" ");
            // Serial.print(c._mot_ant_sx._rpm_target);
            // Serial.print("/");
            // Serial.print(c._mot_ant_sx._rpm);
            // Serial.print(" pwm= ");
            // Serial.print(c._mot_ant_sx._pwm);
            // Serial.print(" outPID =");
            // Serial.print(c.output_pid_AS);
            
            Serial.println();
        }
        delay(333);
    
    }
}

void loop()
{
}