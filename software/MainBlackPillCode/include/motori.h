#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"

#define dim_log_RPM 1024

#define MIN_PWM 80
#define MAX_PWM 255

//TODO: sono define che dovrebbero essere spostati in controller
// ma vengono usate anche qui: cattivo design?
#define IMPULSI_PER_GIRO  (30*7.0f) 
#define INTERVALLO_CAMPIONAMENTO_RPM  20 // us 
#define ALPHA  0.20f  //filtro anti rumore se serve 

class Motore
{

public:

    Motore(int pin1, int pin2, int pin_enc1, int pin_enc2);
    
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
    
    bool lettura_rpm_valida(){ return _rpm_valida;}

    void aggiorna_lettura_rpm();

    void set_target_RPM(float rpm);
    
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
    int _pin_enc1;
    int _pin_enc2;


  private:
    
    bool _rpm_valida=false;
    

    //variabili per calcolo RPM
    volatile unsigned long conta_impulsi_encoder = 0;
             unsigned long ultimo_orario_campionamento = millis();
             unsigned long ultimo_conteggio_impulsi =0 ;

#ifdef LOGGA_RPM
           public:
             float log_RPM[dim_log_RPM];
             int indice_log_RPM = 0;
             bool finito_log = false;
             void logga_RPM()
             {
               log_RPM[indice_log_RPM] = (lettura_rpm_valida(), get_rpm(), 9999.00f);
               indice_log_RPM++;
               if (indice_log_RPM == dim_log_RPM)
                 finito_log = true;
             }

             void stampa_log_RPM()
             {
               for (int i = 0; i < dim_log_RPM; i++)
               {
                 Serial.print(i);
                 Serial.print(" ");
                 Serial.println(log_RPM[i]);
                 logga_RPM();
               }
             }
#endif
};



#endif // MOTORI_H