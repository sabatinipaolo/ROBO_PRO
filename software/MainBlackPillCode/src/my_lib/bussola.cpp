#include "bussola.h"

bool Bussola::begin() {
    if (!Adafruit_QMC5883P::begin())
    {
        // TODO: gestire errore oltre serial...
        while (1)
        {
            Serial.println("ERRORE: bussola non inizializzata");
            delay(1000);
        }
    }
    bussola.setMode(QMC5883P_MODE_NORMAL);
    bussola.setODR(QMC5883P_ODR_50HZ);
    bussola.setOSR(QMC5883P_OSR_4);
    bussola.setDSR(QMC5883P_DSR_2);
    bussola.setRange(QMC5883P_RANGE_8G);
    bussola.setSetResetMode(QMC5883P_SETRESET_ON);

    return true;

};

Bussola bussola;


