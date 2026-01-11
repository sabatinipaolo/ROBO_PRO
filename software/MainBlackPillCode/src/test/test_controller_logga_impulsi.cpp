#include <Arduino.h>
#include "controller.h"

void setup()
{
      
    
    controller.init();
    
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  => LOGGA IMPULSI");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(500);
        };

        Serial.println("Starting  => LOGGA IMPULSI");
    }

    // accendo i motori
    for (int im = 0; im < 4; im++)
    {
        controller.motori[im].muovi(200);
    }

    delay(1000); // atndo che la velocità si stabilizzi;

    for (int im = 0; im < 4; im++)
    {
        controller.motori[im].reset_log_impulsi();
    } // dopo che la velocità è stabile comincio a loggare

    delay((dim_log_impulsi * INTERVALLO_CAMPIONAMENTO_RPM) + 1000); // attendo che si riempia la log +1 sec per prudenza..

    for (int im = 0; im < 4; im++)
    {
        controller.motori[im].stop(); // dopo che la velocità è stabile comincio a loggare
    }
}

void loop()
{

    for (int i = 1; i < dim_log_impulsi; i++)
    {

        Serial.print(i * INTERVALLO_CAMPIONAMENTO_RPM);
        for (int im = 0; im < 4; im++)
        {
            Serial.print(" ");
            Serial.print(controller.motori[im].log_impulsi[i] -
                         controller.motori[im].log_impulsi[i - 1]);
        }
        Serial.println();
        delay(100);
    }

    delay (3000);

}