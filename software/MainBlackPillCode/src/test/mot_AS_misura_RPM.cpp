#include <Arduino.h>
#include "robot.h"

Robot rob;
Motore &m  = rob._mot_ant_sx;

static void ISR_encoder_Motore(){
    m.ISR_encoder();

}

void setup()
{   pinMode(PIN_ENC_AS1, INPUT_PULLUP);
    pinMode(PIN_ENC_AS2, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore, RISING);
    
    
    Serial.begin(115200);
    while (! Serial );
    Serial.println("program started");


    m.muovi(255);
    delay(10000);  //Stabilizzare motore

}

void loop() {

    m.aggiorna_rpm();

    Serial.print("RPM =");
    
    Serial.println(m._rpm);
 
    delay(11);

}


