#include <Arduino.h>
#include "robot.h"


Robot r;


void setup()
{

  Serial.begin(115200);
  while (!Serial1)
    ;
  Serial.println("Starting program ");    
  
  for (int i = 10; i>0;i--){
        Serial.print("inizio misura tra ");
        Serial.println(i);
        delay(333);
    };

  r._mot_ant_dx.muovi(230);
  r._mot_pos_dx.muovi(230);
  r._mot_pos_sx.muovi(230);
  r._mot_ant_sx.muovi(230);


}

void loop(){
  
 if (r._mot_ant_dx._rpm_valida) Serial.println(r._mot_ant_dx._rpm); else Serial.println("----");
 if (r._mot_pos_dx._rpm_valida) Serial.println(r._mot_pos_dx._rpm); else Serial.println("----");
 if (r._mot_pos_sx._rpm_valida) Serial.println(r._mot_pos_sx._rpm); else Serial.println("----");
 if (r._mot_ant_sx._rpm_valida) Serial.println(r._mot_ant_sx._rpm); else Serial.println("----");
 Serial.println();
delay (337);

}

