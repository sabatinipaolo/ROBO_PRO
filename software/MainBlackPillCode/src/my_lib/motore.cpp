#include "motori.h"
Motore::Motore(int pin1, int pin2, int pin_enc1, int pin_enc2)
    : _pin1(pin1), _pin2(pin2), _pin_enc1(pin_enc1),_pin_enc2(pin_enc2)
{
    pinMode(_pin_enc1, INPUT_PULLUP);
    pinMode(_pin_enc2, INPUT_PULLUP);
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
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
    analogWrite(_pin1, LOW);
    analogWrite(_pin2, LOW);
}

void Motore::muovi(int pwm)
{//TODO: ottimizzare 
  if (_pwm == 0 && pwm != 0) {
    reset_lettura_RPM();   // partenza
  }

  if ((_pwm > 0 && pwm < 0) || (_pwm < 0 && pwm > 0)) {
    reset_lettura_RPM();   // cambio direzione
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
{   //TODO: RAFFINARE LE CURVE !!!!!..

  int ritorno = 0;
  if (rpm == 0)
    return 0;
  if (rpm > 0)
    // return (int) map( rpm , 0, 400,0,255);
    // return (int) (0.97*rpm - 173);  //sulcampo  6.3V
    // return (int) (1.31*rpm - 442);  //a vuoto  6.3V
    ritorno = (int)(1.33 * rpm - 439.80 + 15); // a vuoto  6.3V [80-255]  <-- [360 - 500]
                                               //  +10 per avere un po+ di boost...
  if (rpm < 0)
    ritorno = (int)-((1.33 * -rpm - 439.80 + 15));

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
{//TODO: spostare in controller?
// reset_lettura_RPM() va chiamata solo quando:
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

void Motore::aggiorna_lettura_rpm()
{
    noInterrupts();
    unsigned long cnt = conta_impulsi_encoder;
    interrupts();

    long  delta = cnt - ultimo_conteggio_impulsi;
    ultimo_conteggio_impulsi = cnt;
    
    #ifdef LOGGA_IMPULSI
    log_impulsi[indice_impulsi  ] = delta;
    indice_impulsi++;
    #endif

    float rpm_raw =
      (float)delta * 60000.0f / (IMPULSI_PER_GIRO * INTERVALLO_CAMPIONAMENTO_RPM);

    //_rpm = rpm_raw;
    //_rpm += ALPHA * (rpm_raw - _rpm);  //filtro misura se occorre 

    _rpm += ALPHA * (rpm_raw - _rpm);

    #ifdef LOGGA_RPM
    log_rpm[indice_rpm  ] = _rpm;
    indice_rpm++;
    #endif

    
    _rpm_valida = true;

}

void Motore::set_target_RPM(float rpm ){
  //TODO : gestire la dead zone ..qui o in rpm_to_pwm ?
  _rpm_target = rpm;
  int pwm_cmd = (int) rpm_to_pwm( rpm);

  _pwm_base=constrain(pwm_cmd,-255,255);
  _pwm=_pwm_base;
  
  muovi ( _pwm );

}

  