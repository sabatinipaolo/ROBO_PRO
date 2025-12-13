#include <Arduino.h>
#include "robot.h"


#ifdef HAS_OLED_DISPLAY
    #include <Wire.h>
    #include <Adafruit_SSD1306.h>
    #define SCREEN_WIDTH 128 // OLED display width, in pixels
    #define SCREEN_HEIGHT 32 // OLED display height, in pixels
    #define OLED_I2C_ADDR 0x3C
    #define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#endif
#ifdef HAS_OLED_DISPLAY
    Adafruit_SSD1306 display(OLED_RESET);
    
#endif

Robot robot; 


void setup()
{   
    Serial.begin(9600);
    delay(1000); // Give some time to the Serial Monitor to start
    Serial.println("Setup started");

    Wire.begin(); // Join I2C bus as master
    Serial.println("I2C bus started");


    #ifdef HAS_OLED_DISPLAY
    Serial.println("Initializing OLED display...");
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR))
    {   
        while (1)
        {   
            Serial.println(F("SSD1306 allocation failed"));
            digitalWrite(LED_BUILTIN,HIGH);
            delay(300);
            digitalWrite(LED_BUILTIN,LOW);
            delay(300);
            digitalWrite(LED_BUILTIN,HIGH);
            delay(300);
            digitalWrite(LED_BUILTIN,LOW);
            delay(1000);
            digitalWrite(LED_BUILTIN,HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN,LOW);
            delay(300);            
        }
    }
    Serial.println("Initializing OLED display...: done");
    display.setTextSize(3);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.clearDisplay();
    display.setCursor(0, 0); // Start at top-left corner

    display.println("ROBOPRO");
    display.display();
    #endif
    Serial.println("Initializing robot...");
    robot.inizializza();
    Serial.println("initializein robot: done");


}


void loop()
{
  int velocita = 60; int ritardo = 600;

 robot.trasla(0,velocita);  delay(ritardo);robot.stop(); delay(10); 
 robot.trasla(90,velocita); delay(ritardo);robot.stop(); delay(10); 
 robot.trasla(180,velocita);delay(ritardo);robot.stop(); delay(10); 
 robot.trasla(270,velocita);delay(ritardo);robot.stop(); delay(10); 

}