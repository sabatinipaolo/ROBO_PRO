#include "motori.h"
Motore::Motore(int pin1, int pin2, int pin_pwm, int pin_enc1, int pin_enc2)
    : _pin1(pin1), _pin2(pin2), _pin_pwm(pin_pwm),  _pin_enc1(pin_enc1),_pin_enc2(pin_enc2),
       mm_RPM( Media_mobile<float>(DIM_BUFFER_MEDIE_RPM)),
       mm_impulsi(Media_mobile<long int>(DIM_BUFFER_MEDIE_IMPULSI))
{
    pinMode(_pin_enc1, INPUT_PULLUP);
    pinMode(_pin_enc2, INPUT_PULLUP);
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pin_pwm, OUTPUT);
    
    stop();
    aggiorna_lettura_rpm();
   
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
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    analogWrite(_pin_pwm,LOW);
}

void Motore::muovi(int pwm)
{
   #ifdef LOGGA_RPM
      reset_log_RPM();
   #endif
    if ( (_pwm == 0) and (pwm!=0) )  //TODO: Anche per cambio direzione, forse da fermo a in moto è inutile
      { //da fermo a in movimento 
        reset_lettura_RPM();
        mm_impulsi.reset();
      }
    if(pwm==0 ) stop();
    else
    if (pwm > 0)
    {

        _pwm=pwm;
        digitalWrite(_pin1, HIGH);
        digitalWrite(_pin2, LOW);
        analogWrite(_pin_pwm,pwm);
    }
    else if (pwm < 0)
    {
         _pwm=pwm;
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, -pwm);
        analogWrite(_pin_pwm, -pwm);
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
{   //TODO: RAFFINARE LE CURVE !!!!!..

  int ritorno = 0;
  if (rpm == 0)
    return 0;
  if (rpm > 0)
    // return (int) map( rpm , 0, 400,0,255);
    // return (int) (0.97*rpm - 173);  //sulcampo  6.3V
    // return (int) (1.31*rpm - 442);  //a vuoto  6.3V
    //ritorno = (int)(1.33 * rpm - 439.80 + 15); // a vuoto  6.3V [80-255]  <-- [360 - 500]
                                               //  +10 per avere un po+ di boost...
    ritorno = (int)(1.01 * rpm - 166 -55 ); // pile AA a 6VV [120-255]  <-- [270 - 400]
    

  if (rpm < 0)
    ritorno = (int)((1.05 * rpm +170 -160)); // pile AA a 6VV [120-255]  <-- [-260 - 400]

  return ritorno;
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

void Motore::reset_lettura_RPM()
{ //conta_impulsi_encoder=0;
  ultimo_conteggio_impulsi=0;
  _rpm=0;
  //TODO resettare le medie ?
}
void Motore::aggiorna_lettura_rpm()
{
    noInterrupts();
    unsigned long cnt = conta_impulsi_encoder;
    interrupts();

    long  delta = mm_impulsi.filtra(cnt - ultimo_conteggio_impulsi);
    ultimo_conteggio_impulsi = cnt;
    

    float rpm_raw =
      (float)delta * 60000.0f / (IMPULSI_PER_GIRO * INTERVALLO_CAMPIONAMENTO_RPM);

    _rpm=mm_RPM.filtra(rpm_raw);
    #ifdef LOGGA_RPM
      logga_RPM();
    #endif

#ifdef LOGGA_IMPULSI
      //TODO: trasfomrre in metodo ..
      if (!finito_log_impulsi)
      {
        log_impulsi[indice_log_impulsi] = (delta);
        indice_log_impulsi++;
        if (indice_log_impulsi == dim_log_impulsi)
        {
          indice_log_impulsi = 0;
          finito_log_impulsi = true;
        }
      }
#endif
}

void Motore::set_target_RPM(float rpm ){
  //TODO : gestire la dead zone ..qui o in rpm_to_pwm ?
  _rpm_target = rpm;
  int pwm_cmd = (int) rpm_to_pwm( rpm);

  _pwm_base=constrain(pwm_cmd,-255,255);
  _pwm=_pwm_base;
  
  muovi ( _pwm );

}

  