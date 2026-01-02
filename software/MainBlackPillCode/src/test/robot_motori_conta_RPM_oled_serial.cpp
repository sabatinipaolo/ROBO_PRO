#include <Arduino.h>
#include "robot.h"
#define OLED_I2C_ADDR 0x3C


Robot rob ;

void setup(){
    rob.inizializza();
    Serial.begin(115200);
  
    
    delay(1000); // Give some time to the Serial Monitor to start
    
    Serial.println("Setup started");

    rob.controller._mot_ant_dx.orario(155);
    rob.controller._mot_ant_sx.orario(155);
    rob.controller._mot_pos_sx.orario(155);
    rob.controller._mot_pos_dx.orario(155);
}

void loop(){
    
    delay(200);
    rob.oled.stampa4rpm();
    //for (int i=0; i<4;i++) rob.motori[i].aggiorna_rpm();
    Serial.print(Controller::_mot_ant_dx._rpm);
    Serial.print(Controller::_mot_ant_dx._rpm);
    Serial.print(Controller::_mot_ant_dx._rpm);
    Serial.println(Controller::_mot_ant_dx._rpm);



}