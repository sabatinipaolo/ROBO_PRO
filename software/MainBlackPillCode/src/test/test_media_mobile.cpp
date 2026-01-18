#include <Arduino.h>
#include "mediamobile.h"

void setup()
{
    

    Serial.begin();
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("test medie mobili");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio  tra ");
            Serial.println(i);
            delay(333);
        };
    }
}

Media_mobile<int> mi(4);
void loop()
{

    Serial.println("\n\n ");
    for (int i = 1; i < 8; i++)
    {
        Serial.print("inserisco ");
        Serial.print(2*i+1);
        Serial.print(" ");
        Serial.println(mi.filtra(2*i+1));
    };

    delay(1000);
    mi.reset();


}