#include <Arduino.h>

void setup()
{
Serial.begin(115200);

    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  =>   test al volo");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(200);
        };

        Serial.println("Started  =>   test al volo");

    }
}


void loop()
{



}