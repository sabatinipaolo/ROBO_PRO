#include <Arduino.h>

#include <Adafruit_SSD1306.h>

#include "robotpropin.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET 4       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    Serial.begin(115200);

     Wire.setSDA(PIN_I2C_SDA);
     Wire.setSCL(PIN_I2C_SCL);
     Wire.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        
        for (;;)
            Serial.println(F("SSD1306 allocation failed"));
            delay(2000);
    }
    // else{   
        
    //     for (;;)
    //         Serial.println(F("SSD1306 OK !!!!!!!!!"));
    //         delay(2000);

    // }
}

// the loop function runs over and over again forever
void loop()
{
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.println(F("Hello, world!"));
    display.display();
    delay(2000);
}