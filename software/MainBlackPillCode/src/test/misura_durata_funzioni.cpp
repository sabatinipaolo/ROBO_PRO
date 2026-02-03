#include <Arduino.h>
#include "controller.h"
//#include "bussola.h"

//USARE CON   NO_PID NO_RPM NO_BUSSOLA (?)
void setup()
{
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting  =>   misura durata funzioni");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio tra ");
            Serial.println(i);
            delay(200);
        };
    }
    controller.init();
    Serial.println("Starting  =>   misura durata funzioni");
    //bussola.begin();
        for ( int i=0;i<4;i++){
        controller.motori[i].set_target_RPM(500);
    }

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
    //bussola.update_heading();
    ora_fine=micros();

    Serial.print(" Bussola update_heading() ");
    Serial.print(ora_fine -ora_inizio);
    Serial.println(" uSec \n");



    ora_inizio=micros();
    controller._mot_ant_dx.ISR_encoder();
    ora_fine=micros();

    Serial.print(" motore.ISR_encoder()() ");
    Serial.print(ora_fine -ora_inizio);
    Serial.println(" uSec \n");

    Serial.println(" \n\n\n");


}
/* con 4 motori accesi pid e rpm


 controller aggiorna pid 4 motori () 97 uSec 

 controller aggiorna RPM 4 motori()  7 uSec 

 Bussola update_heading() 1 uSec 

 motore.ISR_encoder()() 1 uSec 

 

controller aggiorna pid 4 motori () 90 uSec 

 controller aggiorna RPM 4 motori()  8 uSec 

 Bussola update_heading() 0 uSec 

 motore.ISR_encoder()() 2 uSec 


*/