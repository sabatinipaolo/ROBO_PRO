#ifndef BUSSOLA_H
#define BUSSOLA_H

#include <Adafruit_QMC5883P.h>

class Bussola : public Adafruit_QMC5883P
{
public:
    Bussola() : Adafruit_QMC5883P() {};
    bool begin();

};

extern Bussola bussola;
#endif



