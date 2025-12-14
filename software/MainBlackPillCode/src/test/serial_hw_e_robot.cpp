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
    Serial.begin(115200);   
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
    

}

// the loop function runs over and over again forever
void loop()
{   robot.trasla(0,90);
    Serial.println(F("Hello, world!"));
    delay(2000);
}