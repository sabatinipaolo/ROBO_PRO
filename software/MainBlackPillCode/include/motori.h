#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"
#include "mediamobile.h"

#define dim_log_RPM 300

#define dim_log_impulsi 300


constexpr int DIM_BUFFER_MEDIE_RPM=2;

constexpr int DIM_BUFFER_MEDIE_IMPULSI=8;


#define MIN_PWM 80
#define MAX_PWM 255

//TODO: sono define che dovrebbero essere spostati in controller
// ma vengono usate anche qui: cattivo design?
#define IMPULSI_PER_GIRO  (30*7.0f) 
#define INTERVALLO_CAMPIONAMENTO_RPM  5 // us 
#define ALPHA  0.20f  //filtro anti rumore se serve 

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

    void reset_lettura_RPM();

    void aggiorna_lettura_rpm(int delta_t);

    void set_target_RPM(float rpm);

    float get_target_RPM();

    //TODO: in attesa che  vengano rese private usa comunque ueste:
      float get_rpm(){ return _rpm;};
      float get_pwm(){ return _pwm;};
      float get_pwm_base(){ return _pwm_base;};
    //TODO: in attesa che  vengano rese private usa comunque ueste:
      
    

    float _rpm=0;
   
  
    // TODO: rpm_target pubblica in attesa di refactoring 
    // usare set_target_RPM 
    float _rpm_target;

    int _pwm=0;
    int _pwm_base=0;
    
    int _pin1;
    int _pin2;
    int _pin_pwm;
    int _pin_enc1;
    int _pin_enc2;


  private:
    //variabili per calcolo RPM
    volatile unsigned long conta_impulsi_encoder = 0;
             unsigned long ultimo_orario_campionamento = millis();
             unsigned long ultimo_conteggio_impulsi =0 ;
    
    Media_mobile<float> mm_RPM;  
    //variabili per filtro con media mobile su IMPULSI:
     //se non è stato riempito il buffer la media non è su Dimensione ma sul numero elementi inseriti
 
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