#include <Arduino.h>
#include "robot.h"
//#include <Adafruit_SSD1306.h>

Robot robot; 

void setup()
{ 
}
void loop()
{

 delay(600);robot.trasla(0,100);
 delay(600);robot.trasla(90,100);
 delay(600);robot.trasla(180,100);
 delay(600);robot.trasla(270,100);
 
}