#include <Arduino.h>
#include "robot.h"
#define OLED_I2C_ADDR 0x3C


Robot rob ;

void setup(){
    rob.inizializza();
    Serial.begin(115200);
  
    
    delay(1000); // Give some time to the Serial Monitor to start
    
    Serial.println("Setup started");
    float target= 230.0F;
    int pwm_base= rob.controller._mot_ant_dx.rpm_to_pwm(target);
    rob.controller._mot_ant_dx._rpm_target=(230);
    rob.controller._mot_ant_dx.muovi(pwm_base);

    rob.controller._mot_ant_sx._rpm_target=(230);
    rob.controller._mot_ant_sx.muovi( pwm_base);
    rob.controller._mot_pos_sx._rpm_target=(230);
    rob.controller._mot_pos_sx.muovi( pwm_base);
    rob.controller._mot_pos_dx._rpm_target=(230);
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