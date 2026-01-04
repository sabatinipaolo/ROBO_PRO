#include <Arduino.h>
#include "oled.h"

#include "robot.h"




Robot robot; 


void setup()
{   oled.begin();
    Serial.begin(9600);
    delay(1000); // Give some time to the Serial Monitor to start
    Serial.println("Setup started");

    Wire.begin(); // Join I2C bus as master

    Serial.println("I2C bus started");


 

//    display.println("ROBOPRO");
//    display.display();

    Serial.println("Initializing robot...");
    robot.inizializza();
    Serial.println("initializein robot: done");


}


void loop()
{
  int velocita = 350; int ritardo = 600;

 robot.trasla(0,velocita);  delay(ritardo);robot.stop(); delay(500); 
 oled.stampa_angolo_velocita(0,velocita);
 robot.trasla(90,velocita); delay(ritardo);robot.stop(); delay(500); 
 oled.stampa_angolo_velocita(90,velocita);
 robot.trasla(180,velocita);delay(ritardo);robot.stop(); delay(500); 
 oled.stampa_angolo_velocita(180,velocita);

 robot.trasla(270,velocita);delay(ritardo);robot.stop(); delay(500); 
 oled.stampa_angolo_velocita(270,velocita);

}