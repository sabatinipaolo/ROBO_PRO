#include <Arduino.h>
#include "controller.h"

//#define LOGGA_RPM
#define LOGGA_PID
Controller c;

float target = 400;

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

   Serial.print("tearget= " );
   Serial.print( target );
   Serial.print("pwm from rpm= " );
   Serial.println( c._mot_ant_dx.rpm_to_pwm(target) );
   
   
    Serial.println("\naccendo motori ");

    c._mot_ant_dx._rpm_target = target;
    c._mot_ant_dx.muovi(c._mot_ant_dx.rpm_to_pwm(target));
    //c._mot_ant_dx.muovi(255);

    // c._mot_pos_dx._rpm_target = target;
    // c._mot_pos_dx.muovi(c._mot_pos_dx.rpm_to_pwm(target));

    // c._mot_pos_sx._rpm_target = target;
    // c._mot_pos_sx.muovi(c._mot_pos_sx.rpm_to_pwm(target));

    // c._mot_ant_sx._rpm_target = target;
    // c._mot_ant_sx.muovi(c._mot_ant_sx.rpm_to_pwm(target));

    //while ((millis() - time_inizio) < 120000)
    while (1)
    {
        {//stampa sit.
            float rpm=c._mot_ant_dx._rpm;
            int pwm=c._mot_ant_dx._pwm;


            Serial.print(" ");
            Serial.print(c._mot_ant_dx._rpm_target);
            Serial.print("/");
            Serial.print(rpm);
            Serial.print(" pwm= ");
            Serial.print(pwm);
            // Serial.print(" outPID =");
            // Serial.print(c.output_pid_AD);

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
    // c._mot_ant_dx._rpm_target = 0;
    // c.Timer_per_pid->pause();
    // c.pid_AD.Reset();
    // c._mot_ant_dx.stop();

}

void loop()
{

    for (int i=0;i<1024; i++){
        Serial.print(i);
        Serial.print(" => ");
        Serial.print(target);
        Serial.print(" / ");
        Serial.print(m_AD_log_rpm[i]);
        Serial.print(" out pid ");
        Serial.print(m_AD_log_otuput_pid[i]);
        Serial.println();
        //Serial.print(" / ");
        delay(100);
    }

}