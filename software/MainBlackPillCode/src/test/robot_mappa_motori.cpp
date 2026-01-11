#include <Arduino.h>
#include "controller.h"


//ESEGUIRE CON   -D NO_PID in platform.ini
/////////////////////////////////////////
#define PWM_MIN 80


float medio[4][255];


void setup()
{   controller.init();

    for (int i = 0; i < 4; i++)
            controller.motori[i].muovi(200);

   {
        Serial.begin(115200);
        //   while (!Serial1)
        //     ;
        Serial.println("Starting program ");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio misura tra ");
            Serial.println(i);
            delay(333);
        };
    }


    for (int j_pwm = 0, pwm = PWM_MIN;
         pwm <= 255;
         j_pwm++, pwm += 5)
    {
//d Serial.println(" uno ");
        for (int i = 0; i < 4; i++)
            controller.motori[i].muovi(pwm);

        delay(1500);
//d                                 Serial.println(" due ");
        for (int index_m = 0; index_m < 4; index_m++)
        {   
 //d            Serial.println(" tre ");
            medio[index_m][j_pwm] = 0;

            int n_misure = 0;
            while (n_misure <= 10)
            {
 //d            Serial.println(" quattr ");                
                medio[index_m][j_pwm] += controller.motori[index_m].get_rpm();
                n_misure++;

                delay(100);
            };

            medio[index_m][j_pwm] /= n_misure;
        }

        Serial.print(pwm);
        Serial.print(" ");

        for (int index_m = 0; index_m < 4; index_m++)
        {
            Serial.print(medio[index_m][j_pwm]);
            Serial.print(" ");
        }

        Serial.println();

        for (int i = 0; i < 4; i++)
            controller.motori[i].stop();
        delay(1500);
    }

    
}

void loop()
{
    
}