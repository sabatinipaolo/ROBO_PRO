#include <Arduino.h>
#include "robot.h"


Robot r;


long  ultimo_orario_campionamento_pid=millis();
long INTERVALLO_CAMPIONAMENTO_PID=0 ; // zero siimula il caso più lungo
float _target_rpm = 380.0f, _rpm = 300.3f;
    float Kp = 1.0f;
    float Ki = 0.5f;
    float Kd = 0.00f;

    float integrale = 0.0f;
    float errore_precedente = 0.0f;
void PID_velocita() {


    // if (!rpm_inizializzata)
    //     return; // prima misura non ancora valida
  unsigned long now = millis();
  unsigned long dt = now - ultimo_orario_campionamento_pid;

  if (dt >= INTERVALLO_CAMPIONAMENTO_PID)
  {    // Aggiorna RPM prima di calcolare errore
    r._mot_ant_dx.aggiorna_lettura_rpm();
    float errore = _target_rpm - _rpm;

    unsigned long now = millis();
   // float dt_sec = (now - ultimo_orario_campionamento_pid) / 1000.0f;
    float dt_sec = 1;
   
    ultimo_orario_campionamento_pid = now;

    //integrale += errore * dt_sec;
    integrale += errore ;
    float derivata = (errore - errore_precedente) / dt_sec;
    derivata = (errore - errore_precedente);

    float pwm_corretta = Kp * errore + Ki * integrale + Kd * derivata;

    // Limita PWM tra -255 e 255
    if (pwm_corretta > 255)
      pwm_corretta = 255;
    if (pwm_corretta < -255)
      pwm_corretta = -255;

    r._mot_ant_dx.muovi((int)pwm_corretta);

    errore_precedente = errore;
  }
}


void setup()
{ 
    Serial.begin(11520);
    while (!Serial);
    for (int i = 10; i>0;i--){
        Serial.print("inizio misura tra ");
        Serial.println(i);
        delay(1000);
    }
    //   < 1 uSec
    // long before=micros();
    // r._mot_ant_dx.ISR_encoder();
    // long after=micros();
    // long time=after-before;
    // Serial.print( "ISR_encoder = ");
    // Serial.println(time);

   
    //   < 1 uSec
    //  long before=micros();
    //  r._mot_ant_dx.aggiorna_lettura_rpm();
    //  long after=micros();
    //  long time=after-before;
    //  Serial.print( "aggiornaRPM = ");
    //  Serial.println(time);
    
    //  delay(20);     
     
    // //   37 uSec
    //  long before=micros();
    // PID_velocita();
    //  long after=micros();
    //  long time=after-before;
    //  Serial.print( "PID velociita = ");
    //  Serial.println(time);
    
    //  delay(20);
    //  {
    //  long before=micros();
    // PID_velocita();
    //  long after=micros();
    //  long time=after-before;
    //  Serial.print( "PID velociita = ");
    //  Serial.println(time);
    
    //  delay(20);
    // }

}


void loop() 
{


}

