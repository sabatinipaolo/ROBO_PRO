#include <Arduino.h>
#include "oled.h"

#include "robot.h"




Robot robot; 


void setup()
{   
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
 robot.trasla(90,velocita); delay(ritardo);robot.stop(); delay(500); 
 robot.trasla(180,velocita);delay(ritardo);robot.stop(); delay(500); 
 robot.trasla(270,velocita);delay(ritardo);robot.stop(); delay(500); 

}