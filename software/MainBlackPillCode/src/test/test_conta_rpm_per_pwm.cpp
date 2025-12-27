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
    delay(3000);
    Serial.println("program started");
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore, RISING);
}

void loop() {
for (int pwm=40;pwm<=255;pwm+=5){
    
    m.muovi(-pwm);
    delay(100);
    //calcola media rpm per pwm in un intervallo 30*100 = 3000 ms = 3 sec
    long somma_rpm=0;
    for ( int t = 0 ; t<30; t++){
        m.aggiorna_rpm();
        somma_rpm += m._rpm;
        delay(100);
    };
    
    float media = somma_rpm / 30 ;
 
    Serial.print(pwm);
    Serial.print(" ");
    Serial.println(media);
 
    m.stop();delay(100);

}

}
