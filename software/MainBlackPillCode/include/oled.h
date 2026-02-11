#ifndef OLED_H
#define OLED_H

#include "controller.h"

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define OLED_I2C_ADDR 0x3C

class Oled : public Adafruit_SSD1306
{ //TODO: di fatto oled è un singleton trattarlo come tale

public:
    #define OLED_RESET -1
    Oled() : Adafruit_SSD1306(OLED_RESET) {};
    bool begin();
    void stampa4rpm(Controller &c);
    void stampa_angolo_velocita(float alfa, int velocita);


    void stampa4float( float,float,float,float);
private:
};

extern Oled oled;

#endif