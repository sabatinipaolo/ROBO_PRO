#include "oled.h"

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

void Oled::stampa4rpm(Controller & c){
    stampa4float(c._mot_ant_sx._rpm,c._mot_ant_dx._rpm,
                 c._mot_pos_sx._rpm,c._mot_pos_dx._rpm );
}

void Oled::stampa4float(float f1, float f2, float f3, float f4)
{
    clearDisplay();
    setCursor(0, 0); 

    char str[5];
    dtostrf(f1, 5, 0, str);
    print(str);

    dtostrf(f2, 5, 0, str);
    println(str);

    dtostrf(f3, 5, 0, str);
    print(str);

    dtostrf(f4, 5, 0, str);
    println(str);

    display();
}

Oled oled ;
