#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"

#define MIN_PWM 80
#define MAX_PWM 255

#define PPR 210   //pulse per revolutio 7 ppr * 30 gear ratio  

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
    void aggiorna_rpm();

    
    
    volatile long encoderCount = 0;    
    unsigned long lastTime = 0;
    long lastCount = 0;
    float _rpm=0;

    private:
    int _pin1;
    int _pin2;
    int _pin_enc1;
    int _pin_enc2;
    
  
    int _rpm_target;

};

Motore::Motore(int pin1, int pin2, int pin_enc1, int pin_enc2)
    : _pin1(pin1), _pin2(pin2), _pin_enc1(pin_enc1),_pin_enc2(pin_enc2)
{
    pinMode(_pin_enc1, INPUT_PULLUP);
    pinMode(_pin_enc2, INPUT_PULLUP);
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    stop();
    
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
    analogWrite(_pin1, LOW);
    analogWrite(_pin2, LOW);
}

void Motore::muovi(int pwm)
{

    if (pwm >= 0)
    {
        //antiorario(pwm);
        analogWrite(_pin1, pwm);
        analogWrite(_pin2, LOW);

    }
    else if (pwm < 0)
    {
        //orario(-pwm);
        analogWrite(_pin1, LOW);
        analogWrite(_pin2, -pwm);
    }

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
    encoderCount++;
  }
  else
  {
    encoderCount--;
  }
}

void Motore::aggiorna_rpm()
{
    unsigned long currentTime = millis();

    noInterrupts();
    long count = encoderCount;
    interrupts();

    long delta_impulsi = count - lastCount;
    
    float dt = (currentTime - lastTime) / 1000.0;

    _rpm = (delta_impulsi / (float)PPR) * (60.0 / dt);
    
    // float Dt_in_ms = (currentTime - lastTime);

    // _rpm = (delta_impulsi / PPR ) / (Dt_in_ms / (60*1000));

    lastCount = count;
    lastTime = currentTime;

}

#endif // MOTORI_H