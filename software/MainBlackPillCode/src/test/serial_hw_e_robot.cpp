#include <Arduino.h>
#include "robot.h"

Robot robot;
void setup()
{
    Serial.begin(115200);   
  
    

}

// the loop function runs over and over again forever
void loop()
{   robot.trasla(0,90);
    Serial.println(F("Hello, world!"));
    delay(2000);
}