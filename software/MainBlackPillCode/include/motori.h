#ifndef MOTORI_H
#define MOTORI_H

#include <Arduino.h>
#include "robotpropin.h"

#define MIN_PWM 80

class Motore
{
public:
    Motore(int pinA, int pinB);
    
    Motore(const Motore&) = delete;             //impedisce copie di oggetti motori, Motore m(m2) (costruttore copia) genera errore
    Motore& operator=(const Motore&) = delete;  // m1=m2 genera errore
                                                // vedi qui: https://www.stroustrup.com/C++11FAQ.html#default
    
    void orario(int pwm);
    void antiorario(int pwm);
    void stop();
    void muovi(int pwm);

    void test_avanti_indietro(int pwm);

private:
    int _pin1;
    int _pin2;
};

Motore::Motore(int pin1, int pin2)
    : _pin1(pin1), _pin2(pin2)
{

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
{
    orario(pwm);
    delay(2000);
    stop();
    delay(1000);
    antiorario(pwm);
    delay(2000);
    stop();
    delay(1000);
}

#endif // MOTORI_H