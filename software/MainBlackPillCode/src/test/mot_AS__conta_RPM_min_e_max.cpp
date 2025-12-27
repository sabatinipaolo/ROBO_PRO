#include <Arduino.h>
#include "robot.h"

Robot rob;
Motore &m  = rob._mot_ant_sx;

static void ISR_encoder_Motore(){
    m.ISR_encoder();
}

void setup()
{
    Serial.begin(115200);
    while (!Serial) ;
    Serial.println("program started");
    pinMode(PIN_ENC_AS1, INPUT_PULLUP);
    pinMode(PIN_ENC_AS2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore, RISING);
        
    m.muovi(255);
    delay(12);
    float rpm_min=10000;
    float rpm_max=-10000;
    for (int misura = 0; misura < 10; misura++)
    {
         rpm_min=10000;
         rpm_max=-10000;
        for (int i=0 ;i <10;i++){

                m.aggiorna_rpm();
                if (m._rpm> rpm_max) 
                    rpm_max = m._rpm;

                if (m._rpm < rpm_min)
                    rpm_min = m._rpm;

                delay(1313);

        };
        Serial.println(misura);
        Serial.print("rpm min ");
        Serial.print(rpm_min);
        Serial.print("rpm max ");
        Serial.println(rpm_max);
        Serial.print("delta ");
        Serial.println(rpm_max-rpm_min);
    }
     
}


void loop() 
{
}

