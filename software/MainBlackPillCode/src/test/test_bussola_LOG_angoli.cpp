#include <Arduino.h>
#include "bussola.h"

void setup()
{
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("INIZIO CALIBRAZIONE TRA ");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(330);
        };
    }
    bussola.begin();
    bussola.lb.reset();
 

}

void loop()
{
    if (!bussola.lb.finito_di_loggare()){
        bussola.update_heading();
        delay(20);

    }
    else{
        Serial.println("\nLOGGGG");
        for(int i =0 ; i< bussola.lb.get_dimensione(); i++){
            Serial.println(bussola.lb.get_valore_loggato(i));
            delay(100);
        };
        Serial.println("\nFINITO LOGGGG");
       
    }


}