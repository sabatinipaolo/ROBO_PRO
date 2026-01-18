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

    //set_calibration(800.00,41.00,103.00,0.74,0.80,2.52);
    //set_calibration(921.00,107.00,111.00,0.73,0.78,2.97);
    //set_calibration(662.00,290.00,-442.00,0.95,0.78,1.51);
    set_calibration(915.5, 221.5, 19.5,  0.7405405405405405, 0.7215951843491347 ,3.7905138339920947 );
    
    // while ( !isDataReady()) 
    // { Serial.println("non sono pronto");
    //    delay(20);};
    update_heading();
    _heading_iniziale=mm_bussola.filtra(_heading);
    // Serial.println("_heading_iniziale");
    // Serial.println(_heading_iniziale);
      
    return true;

};

void Bussola::set_calibration(float ox, float oy, float oz,
                              float sx, float sy, float sz)
{
    _offset_x = ox;
    _offset_y = oy;
    _offset_z = oz;
    _scale_x = sx;
    _scale_y = sy;
    _scale_z = sz;
};

void Bussola::calibrazione()
{
    int16_t min_x=INT16_MAX ;
    int16_t min_y=INT16_MAX ;
    int16_t min_z=INT16_MAX ;

    int16_t max_x=INT16_MIN ;
    int16_t max_y=INT16_MIN ;
    int16_t max_z=INT16_MIN ;

    float offset_x =0 ;
    float offset_y =0 ;
    float offset_z =0 ;

    
    float scale_x = 0 ;
    float scale_y = 0 ;
    float scale_z = 0 ;

    //messaggio di start sulla seriale?

    unsigned long int ora_inizio = millis();
    while ((millis() - ora_inizio)< 120000)
    {
        if (isDataReady()) {
        int16_t x, y, z;

        if (getRawMagnetic(&x, &y, &z)) {
                min_x = min(min_x, x);            
                min_y = min(min_y, y);
                min_z = min(min_z, z);

                max_x = max(max_x, x);            
                max_y = max(max_y, y);
                max_z = max(max_z, z);
        }
    };

    offset_x = (max_x + min_x) / 2;
    offset_y = (max_y + min_y) / 2;
    offset_z = (max_z + min_z) / 2;

    float avg_delta_x = (max_x - min_x) / 2;
    float avg_delta_y = (max_y - min_y) / 2;
    float avg_delta_z = (max_z - min_z) / 2;

    float avg_delta = (avg_delta_x + avg_delta_y + avg_delta_z) / 3;

    scale_x = avg_delta / avg_delta_x;
    scale_y = avg_delta / avg_delta_y;
    scale_z = avg_delta / avg_delta_z;

    
    
};

    set_calibration(offset_x,offset_y,offset_z,scale_x,scale_y,scale_z);

    Serial.print("bussola.set_calibration(");
    Serial.print(offset_x);
    Serial.print(",");
    Serial.print(offset_y);
    Serial.print(",");
    Serial.print(offset_z);
    Serial.print(",");
    Serial.print(scale_x);
    Serial.print(",");
    Serial.print(scale_y);
    Serial.print(",");
    Serial.print(scale_z);
    Serial.println(";");

}

bool Bussola::get_cal_magnetic(int16_t* x, int16_t* y, int16_t* z){

    if (!getRawMagnetic(x, y, z))
        return false;

    *x = (int16_t)(*x - _offset_x) * _scale_x;
    *y = (int16_t)(*y - _offset_y) * _scale_y;
    *z = (int16_t)(*z - _offset_z) * _scale_z;

    return true;
}

void Bussola::update_heading(){
    //Serial.println("Get_heading");

    if (!isDataReady())
        {    //Serial.println("     non sono pronti i dati");

        return;
        };
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;

    if (!get_cal_magnetic(&x, &y, &z)){
        //Serial.println("       non posso otttenere cal ");

        return ;
    }
    //Serial.println("Calcolo heading");
	
    float heading =  atan2( x, y) * (180.0 / PI) - _heading_iniziale ;

    //TODO : fare meglio
    if (heading < -180)  heading +=360;
    if (heading >  180)  heading -=360;
    #ifdef LOGGA_BUSSOLA
        lb.logga(heading);
    #endif   
    _heading= heading;
   

    
}

void Bussola::stampa_su_seriale_raw_xyz()
{
    int16_t x, y, z;
    if (bussola.getRawMagnetic(&x, &y, &z))
    {
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.println(z);
    };
}

void Bussola::stampa_su_seriale_cal_xyz()
{
    int16_t x, y, z;
    if (bussola.get_cal_magnetic(&x, &y, &z))
    {
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.println(z);
    };
}



void Bussola::stampa_per_plot_py(){
    unsigned long int ora_inizio=millis();
    while(millis()-ora_inizio < 60*1000*2){
        stampa_su_seriale_raw_xyz();
        delay(10);
    }


}

Bussola bussola;
