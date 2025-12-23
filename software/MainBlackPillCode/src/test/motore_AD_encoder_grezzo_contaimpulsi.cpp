#include <Arduino.h>
#include "motori.h"


Motore m(PIN_MOT_AD1, PIN_MOT_AD2, PIN_ENC_AD1, PIN_ENC_AD2);



static void ISR_encoder_Motore(){
    m.ISR_encoder();

}

long last_time=0;

void setup(){
    m.stop();
    Serial.begin(115200);
    m.muovi(+300);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), ISR_encoder_Motore, RISING);
}

void loop(){
    delay(200);
    m.aggiorna_rpm();
    Serial.print( "rpm = "); Serial.println(m._rpm);
    Serial.print( "Ecount= "); Serial.println(m.encoderCount);
    

}