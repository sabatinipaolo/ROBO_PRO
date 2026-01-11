#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"

#define dim_log_RPM 300

#define dim_log_impulsi 300


#define DIM_BUFFER_MEDIE_RPM 8

#define DIM_BUFFER_MEDIE_IMPULSI 8


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
    //variabili per calcolo RPM
    volatile unsigned long conta_impulsi_encoder = 0;
             unsigned long ultimo_orario_campionamento = millis();
             unsigned long ultimo_conteggio_impulsi =0 ;
    
    //variabili per filtro con media mobile :
    float buffer[DIM_BUFFER_MEDIE_RPM]={0};
    int bufferSize=DIM_BUFFER_MEDIE_RPM;
    int currentIndex=0;
    float sum=0;
    bool bufferFilled=false;  //se non è stato riempito il buffer la media non è su Dimensione ma sul numero elementi inseriti
    
    //variabili per filtro con media mobile su IMPULSI:
    long int buffer_impulsi[DIM_BUFFER_MEDIE_IMPULSI]={0};
    int bufferSize_impulsi=DIM_BUFFER_MEDIE_IMPULSI;
    int currentIndex_impulsi=0;
    float sum_impulsi=0;
    bool buffer_impulsi_Filled=false;  //se non è stato riempito il buffer la media non è su Dimensione ma sul numero elementi inseriti
 

    float filtra(float nuova_RPM) {
      sum -= buffer[currentIndex];
      buffer[currentIndex] = nuova_RPM;
      sum += nuova_RPM;
      currentIndex = (currentIndex + 1) % bufferSize;
      if(currentIndex == 0) bufferFilled = true;  

      int validElements = ( bufferFilled ? bufferSize : currentIndex) ;
      if(validElements > 0) {
        float media = sum / validElements;
        return ( (media > 0) ? (int) (media+0.5f) : (int) (media -0.5f)) ;

      } else {
        return 0;
      }
    }

    void reset_medie_RPM()
    {
      currentIndex = 0;
      sum = 0.0;
      bufferFilled = false;
      for (int i = 0; i < bufferSize; i++)  //TODO: Non sarebbe inutile?
        buffer[i] = 0.0;
    }

    long int filtra_impulsi( long int num_impulsi) {
      
      sum_impulsi -= buffer_impulsi[currentIndex_impulsi];
      buffer_impulsi[currentIndex_impulsi] = num_impulsi;
      sum_impulsi += num_impulsi;
      currentIndex_impulsi = (currentIndex_impulsi + 1) % bufferSize_impulsi;
      if(currentIndex_impulsi == 0) buffer_impulsi_Filled = true;  

      int validElements = ( buffer_impulsi_Filled ? bufferSize_impulsi : currentIndex_impulsi) ;
      if(validElements > 0) {
        float media = sum_impulsi / validElements;
        return ( (media > 0) ? (int) media+0.5f : media-0.5f) ;
      } else {
        return num_impulsi;
      }
    }
    
    void reset_medie_impulsi()
    {
      currentIndex_impulsi = 0;
      sum_impulsi = 0.0;
      buffer_impulsi_Filled = false;
      for (int i = 0; i < bufferSize_impulsi; i++)  //TODO: Non sarebbe inutile?
        buffer_impulsi[i] = 0.0;
    }



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