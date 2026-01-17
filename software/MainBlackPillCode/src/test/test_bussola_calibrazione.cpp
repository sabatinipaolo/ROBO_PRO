#include <Arduino.h>
#include "bussola.h"

void setup()
{   
   

    Serial.begin();
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

    // int16_t x=-0.3;
    // int16_t y=-1;

    // Serial.print( "atan2 di ");
    // Serial.print( x );
    // Serial.print(", ");
    // Serial.print(y);
    // Serial.print(")=");
    // Serial.println( atan2(x,y)* (180.0 / PI));

    bussola.begin();
    //bussola.calibrazione();

    delay(2000);

}


void loop()
{
    
    // bussola.stampa_su_seriale_raw_xyz();
    // delay(100);

            //bussola.stampa_su_seriale_cal_xyz();

           Serial.println ( bussola.get_heading());
           bussola.update_heading();
           delay(333);

            // Serial.print("bussola.set_calibration(");
            // Serial.print(bussola._offset_x);
            // Serial.print(",");
            // Serial.print(bussola._offset_y);
            // Serial.print(",");
            // Serial.print(bussola._offset_z);
            // Serial.print(",");
            // Serial.print(bussola._scale_x);
            // Serial.print(",");
            // Serial.print(bussola._scale_y);
            // Serial.print(",");
            // Serial.print(bussola._scale_z);
            // Serial.println(");");
            //;delay(1000);
}