#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"
#include "mediamobile.h"

//costanti per eventuale log
constexpr int dim_log_RPM=300;
constexpr int dim_log_impulsi=300; 


//constexpr int DIM_BUFFER_MEDIE_RPM=2; 
constexpr int DIM_BUFFER_MEDIE_IMPULSI=8;

constexpr int IMPULSI_PER_GIRO=(30*7.0f) ;
constexpr float ALPHA= 0.20f ;// costante per filtro ema su rpm 

class Motore
{

public:

    Motore(int pin1, int pin2, int pin_pwm, int pin_enc1, int pin_enc2);
    
    Motore(const Motore&) = delete;             //impedisce copie di oggetti motori, Motore m(m2) (costruttore copia) genera errore
    Motore& operator=(const Motore&) = delete;  // m1=m2 genera errore
                                                // vedi qui: https://www.stroustrup.com/C++11FAQ.html#default
    
    void orario(int pwm);
    void antiorario(int pwm);
    void stop();
    void muovi(int pwm);

    void test_avanti_indietro(int pwm);

    int rpm_to_pwm(int rpm);
    void ISR_encoder();

    void aggiorna_lettura_rpm(int delta_t);

    void set_target_RPM(float rpm);

    float get_target_RPM();
    float* get_address_target_RPM(){return &_rpm_target;};
      float get_rpm(){ return _rpm;};
      float* get_address_rpm(){return &_rpm;};

      float get_pwm(){ return _pwm;};
    
  private:
    float _rpm=0;
    float _rpm_target;
    int _pwm=0;
    int _pin1;
    int _pin2;
    int _pin_pwm;
    int _pin_enc1;
    int _pin_enc2;

    //variabili per calcolo RPM
    volatile unsigned long conta_impulsi_encoder = 0; //dovremmo aver un overflof ogni 600 ore circa ..
             unsigned long ultimo_conteggio_impulsi =0 ;
    
    //Media_mobile<float> mm_RPM;  
 
    Media_mobile<long int> mm_impulsi; 
   



#ifdef LOGGA_RPM
           public:
             float log_RPM[dim_log_RPM];
             int indice_log_RPM = 0;
             bool finito_log = false;
             void reset_log_RPM(){
              indice_log_RPM=0;
              finito_log= false;
             }
             void logga_RPM()
             {
               if (finito_log) return;

               log_RPM[indice_log_RPM] = get_rpm();
               indice_log_RPM++;
               if (indice_log_RPM == dim_log_RPM)
               {
                 finito_log = true;
               }
             }

#endif

#ifdef LOGGA_IMPULSI
           public:
             long int  log_impulsi[dim_log_impulsi];
             int indice_log_impulsi = 0;
             bool finito_log_impulsi = false;

             void reset_log_impulsi(){
              indice_log_impulsi=0;
              finito_log_impulsi= false;
             }

#endif
};



#endif // MOTORI_H