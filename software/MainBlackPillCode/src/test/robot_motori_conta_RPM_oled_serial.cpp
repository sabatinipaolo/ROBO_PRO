#include <Arduino.h>
#include "robot.h"
#define OLED_I2C_ADDR 0x3C


Robot rob ;

void setup(){
    rob.inizializza();

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
    
    Serial.println("Setup started");
    float target= 350.0F;
    
    Serial.print("pwm base= ");
    Serial.print(rob.controller._mot_ant_dx.rpm_to_pwm(target));

    int pwm_base= rob.controller._mot_ant_dx.rpm_to_pwm(target);
    rob.controller._mot_ant_dx._rpm_target=(target);
    rob.controller._mot_ant_dx.muovi(pwm_base);

    rob.controller._mot_ant_sx._rpm_target=(target);
    rob.controller._mot_ant_sx.muovi( pwm_base);
    rob.controller._mot_pos_sx._rpm_target=(target);
    rob.controller._mot_pos_sx.muovi( pwm_base);
    rob.controller._mot_pos_dx._rpm_target=(target);
    rob.controller._mot_pos_dx.muovi( pwm_base);
}

void loop(){
    
    delay(200);
    rob.oled.stampa4rpm();

    Serial.print(" target ");
    Serial.print(rob.controller._mot_ant_dx._rpm_target);
    Serial.print(" rpm ");
    Serial.print(rob.controller._mot_ant_dx._rpm);
    Serial.print(" pwm ");
    Serial.print(rob.controller._mot_ant_dx._rpm_target);
    Serial.print(" outpid ");
    Serial.println(Controller::output_pid_AD);



}