#include <Arduino.h>
#include <QuickPID.h>


//#define LOGGA_IMPULSI 
//#define LOGGA_RPM 

#include "robot.h"


Robot r ;
Motore & m = r._mot_pos_dx;

void setup()
{
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting program ");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio misura tra ");
            Serial.println(i);
            delay(333);
        };
    }

    Serial.println("accendo motore ");
           
    
    m.muovi(120);

    delay(512*10); //tempo per riempire la log 

    r.Timer_per_rpm->detachInterrupt();
    m.stop();

#ifdef LOGGA_RPM
    Serial.println("fermo motore ");
    Serial.println("indice log = ");
    Serial.println(m.indice_rpm);
#endif           


}
int volte=0;
void loop()
{
  if (volte <10 ){
    Serial.println("STAMPO LOG ");
    Serial.println("indice log = ");
        #ifdef LOGGA_IMPULSI
        Serial.print(m.indice_impulsi);
        #endif
        #ifdef LOGGA_RPM
        Serial.print(m.indice_rpm);
        #endif    
    for (int i=0;i<256; i++){
        #ifdef LOGGA_IMPULSI
        if (i==m.indice_impulsi ){ 
            Serial.print(" *** ");
        }

        Serial.print(m.log_impulsi[i]);
        #endif

        #ifdef LOGGA_RPM
          if (i==m.indice_rpm ){ 
            Serial.print(" *** ");
        }
        Serial.print(m.log_rpm[i]);
        #endif
        
        Serial.print(" , "); 

    }
    Serial.println();
    volte++;
  }

}