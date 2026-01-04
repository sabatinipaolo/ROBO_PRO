#include <Arduino.h>
#include "controller.h"

void setup()
{    
    controller.init();
    controller.enable_PID();

     Serial.begin(115200);

    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting program ");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(2000);
        };
    }





}

void loop()
{
    int pwm=200;

    
    for ( int dir=-1; dir <=1 ;dir+=2)
    {
        for (int i=0 ; i<4 ;i++){
            // Serial.print("accendo il motore ");
            // Serial.print(i);
            // Serial.print(" pwm= ");
            // Serial.print( pwm*dir );
            
            controller.motori[i].muovi(pwm);
            delay(3000);
        };



        delay (5000);

        for (int i=0 ; i<4 ;i++){
            // Serial.print("spengo il motore ");
            // Serial.print(i);
            // Serial.print(" pwm= ");
            // Serial.print( pwm*dir );
            
            controller.motori[i].stop();
            delay(3000);
        };

    }
}