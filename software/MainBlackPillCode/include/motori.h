#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"

#define MIN_PWM 80
#define MAX_PWM 255

//#define PPR 210   //pulse per revolutio 7 ppr * 30 gear ratio  

constexpr float IMPULSI_PER_GIRO = 30*7.0f ;
constexpr float INTERVALLO_CAMPIONAMENTO_RPM = 10.0f; 
constexpr float ALPHA = 0.50f;  //filtro anti rumore se serve 

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
    void resetRPM();

    void aggiorna_rpm();
    float _rpm=0;
    bool _rpm_valida=false;

    int _pwm=0;
    int _pin1;
    int _pin2;
    int _pin_enc1;
    int _pin_enc2;
private:
  

    //variabili per calcolo RPM
    volatile unsigned long conta_impulsi_encoder = 0;
             unsigned long ultimo_orario_campionamento = millis();
             unsigned long ultimo_conteggio_impulsi =0 ;
};


Motore::Motore(int pin1, int pin2, int pin_enc1, int pin_enc2)
    : _pin1(pin1), _pin2(pin2), _pin_enc1(pin_enc1),_pin_enc2(pin_enc2)
{
    pinMode(_pin_enc1, INPUT_PULLUP);
    pinMode(_pin_enc2, INPUT_PULLUP);
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    stop();
    aggiorna_rpm();
   
};

void Motore::antiorario(int pwm)
{
    muovi(pwm);
}

void Motore::orario(int pwm)
{
    muovi(-pwm);
}

void Motore::stop()
{
    _pwm=0;
    analogWrite(_pin1, LOW);
    analogWrite(_pin2, LOW);
}

void Motore::muovi(int pwm)
{//TODO: ottimizzare 
  if (_pwm == 0 && pwm != 0) {
    resetRPM();   // partenza
  }

  if ((_pwm > 0 && pwm < 0) || (_pwm < 0 && pwm > 0)) {
    resetRPM();   // cambio direzione
  };
    if(pwm==0 ) stop();
    else
    if (pwm > 0)
    {
        //antiorario(pwm);
        _pwm=pwm;
        analogWrite(_pin1, pwm);
        analogWrite(_pin2, LOW);

    }
    else if (pwm < 0)
    {
        //orario(-pwm);
         _pwm=pwm;
        analogWrite(_pin1, LOW);
        analogWrite(_pin2, -pwm);
    };

}

void Motore::test_avanti_indietro(int pwm)
{   //TODO: eliminare e creare test apposito
    orario(pwm);
    delay(2000);
    stop();
    delay(1000);
    antiorario(pwm);
    delay(2000);
    stop();
    delay(1000);
}

int Motore::rpm_to_pwm(int rpm)
{   //TODO: ragionarci sopra...
    if (rpm==0) return 0;    
    return map(rpm,0,500,MIN_PWM,MAX_PWM);
};

void Motore::ISR_encoder()
{ // semplicissima ISR da usare su interrupt del pin_enc1 su RISING
  // Determina la direzione usando il canale B
  if (digitalRead(_pin_enc2) == HIGH)
  {
    conta_impulsi_encoder++;
  }
  else
  {
    conta_impulsi_encoder--;
  }
}
void Motore::resetRPM()
{
// resetRPM() va chiamata solo quando:
// - il motore parte da fermo
// - il motore si ferma
// - si cambia direzione
// - si cambia modalità di controllo

  noInterrupts();
  ultimo_conteggio_impulsi = conta_impulsi_encoder;
  interrupts();
  _rpm_valida = false;

  ultimo_orario_campionamento = millis();

}

void Motore::aggiorna_rpm()
{
    noInterrupts();
    unsigned long cnt = conta_impulsi_encoder;
    interrupts();

    long  delta = cnt - ultimo_conteggio_impulsi;
    ultimo_conteggio_impulsi = cnt;

    float rpm_raw =
      (float)delta * 60000.0f / (IMPULSI_PER_GIRO * INTERVALLO_CAMPIONAMENTO_RPM);

    //_rpm = rpm_raw;

    _rpm += ALPHA * (rpm_raw - _rpm);  //filtro misura se occorre 
  
    _rpm_valida = true;

}


  

#endif // MOTORI_H