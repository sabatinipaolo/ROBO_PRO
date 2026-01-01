#ifndef OLED_H
#define OLED_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define OLED_I2C_ADDR 0x3C

class Oled : public Adafruit_SSD1306
{

public:
#define OLED_RESET -1
    Oled() : Adafruit_SSD1306(OLED_RESET) {};
    bool begin();

private:
};

bool Oled::begin()
{
    if (!Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR))
    { // TODO: testare simulando un guasto oled ...
        pinMode(LED_BUILTIN, OUTPUT);
        while (1)
        {
            digitalWrite(LED_BUILTIN, LOW);
            delay(300);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(300);

            Serial.println(F("SSD1306 allocation failed"));
            ; // Don't proceed, loop forever
        }
    }
    setTextSize(2);              // Normal 1:1 pixel scale
    setTextColor(SSD1306_WHITE); // Draw white text

    return true;
}

#endif