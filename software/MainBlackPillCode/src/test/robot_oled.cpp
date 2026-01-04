#include <Arduino.h>
#include "robot.h"
#include "oled.h"

#define OLED_I2C_ADDR 0x3C
Robot r;


void setup() {
Serial.begin(115200);
r.oled.begin();
}
String s[]=   {"T",
               "OT",
               "BOT",
               "OBOT",
               "ROBOT",
               " ROBOT",
               "D ROBOT",
               "ED ROBOT",
               "OLED ROBOT",
               "           " 
            };

int i=0;  
void loop() {
     Serial.println(s[i]);

  r.oled.clearDisplay();
  r.oled.setCursor(0, 0); // Start at top-left corner

  r.oled.println( s[i]);
  //r.oled.println(F("1234567890"));
 
  r.oled.display();
  
  i++;
  if (i == 10) i=0;
  delay(100);

}
