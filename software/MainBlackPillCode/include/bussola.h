#ifndef BUSSOLA_H
#define BUSSOLA_H

#include <Adafruit_QMC5883P.h>

class Bussola : public Adafruit_QMC5883P
{
public:
    Bussola() : Adafruit_QMC5883P() {};
    bool begin();

    void set_calibration(float ox, float oy,float oz,
                         float sx, float sy,float sz);
    void calibrazione();

    bool get_cal_magnetic(int16_t *x, int16_t *y, int16_t *z);
    float get_heading(){return _heading;}
    void update_heading();
    void stampa_su_seriale_raw_xyz();
    void stampa_su_seriale_cal_xyz();
    void stampa_per_plot_py();

private:
    float _heading = 0;
    float _heading_iniziale = 0;

public:
    float _offset_x = 0;
    float _offset_y = 0;
    float _offset_z = 0;
    float _scale_x = 0;
    float _scale_y = 0;
    float _scale_z = 0;
};

extern Bussola bussola;
#endif



