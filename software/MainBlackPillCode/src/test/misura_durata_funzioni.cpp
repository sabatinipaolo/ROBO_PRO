#include <Arduino.h>
#include "controller.h"
#include "bussola.h"

//USARE CON   NO_PID NO_RPM NO_BUSSOLA (?)
void setup()
{
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  =>   test_controller_RPM_e_PID");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(200);
        };
    }
    controller.init();
    bussola.begin();

}

    unsigned long int ora_inizio,ora_fine;

void loop()
{
    delay(1000);
    ora_inizio=micros();
    controller.aggiorna_PID_dei_quattro_motori();
    ora_fine=micros();

    Serial.print(" controller aggiorna pid 4 motori () ");
    Serial.print(ora_fine -ora_inizio);
    Serial.println(" uSec \n");



    ora_inizio=micros();
    controller.aggiorna_RPM_dei_quattro_motori();
    ora_fine=micros();

    Serial.print(" controller aggiorna RPM 4 motori()  ");
    Serial.print(ora_fine -ora_inizio);
    Serial.println(" uSec \n");

    ora_inizio=micros();
    bussola.update_heading();
    ora_fine=micros();

    Serial.print(" Bussola update_heading() ");
    Serial.print(ora_fine -ora_inizio);
    Serial.println(" uSec \n");




}