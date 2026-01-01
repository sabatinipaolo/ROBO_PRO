#include <Arduino.h>
#include <QuickPID.h>

#include "robot.h"


Robot r ;
Motore & m = r._mot_pos_sx;
float output;
// //QuickPID myPID(&Input, &Output, &Setpoint);
QuickPID myPID(&m._rpm, &output, &m._rpm_target);
HardwareTimer *Timer_per_PID  = new HardwareTimer(TIM9);


#define MAX_LOG_PID  1024
float log_pid_output[MAX_LOG_PID];
float log_pid_rpm_in_input[MAX_LOG_PID];

u_int16_t indice_log_pid =0;


void handlePIDSample() { // Funzione chiamata dal timer
  float rpm_input= m._rpm;
  if (m._rpm_valida && myPID.Compute())
  { // Qui applica l'output alla PWM del motore
    float pwm_cmd  = m._pwm_base + output;
    pwm_cmd = constrain(pwm_cmd, 0, 255);
       
    m.muovi((int) pwm_cmd);

    // log pid :
    if (indice_log_pid < 1024)
    {
      log_pid_rpm_in_input[indice_log_pid] = rpm_input;
      log_pid_output[indice_log_pid] = output;
      indice_log_pid++;
    };
  }
}


//float Kp =2, Ki = 4, Kd = 0;
//float Kp =3, Ki = 0, Kd = 0; 
//float Kp =3, Ki = 2, Kd = 0; //ancora lento
//float Kp =3, Ki = 3, Kd = 0; //ancolra lento
//float Kp =3, Ki = 4, Kd = 0; // il meglio che ho ottenuto ma misura ancora sotto
//definito fee_forward
//float Kp =0.8, Ki = 0.2, Kd = 0; 
//float Kp =0.8, Ki = 0.3, Kd = 0; 
float Kp =0.8, Ki = 0.4, Kd = 0; 

void setup()
{
    { // starting serial e programma
        Serial.begin(115200);
        while (!Serial1)
            ;
        Serial.println("Starting program ");

        for (int i = 10; i > 0; i--)
        {
            Serial.print("inizio misura tra ");
            Serial.println(i);
            delay(333);
        };
    }

myPID.SetTunings(Kp, Ki, Kd);
myPID.SetOutputLimits(0,255);     // Set and clamps the output to (0-255 by default)
myPID.SetSampleTimeUs(INTERVALLO_CAMPIONAMENTO_RPM * 1000);
myPID.SetMode(QuickPID::Control::timer);

 Timer_per_PID->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_RPM, HERTZ_FORMAT); // se intervallo=20ms allora freq = 1000 / 20 = 50 ......
 Timer_per_PID->attachInterrupt(handlePIDSample);
 Timer_per_PID->resume();



m._rpm_target = 320 ;
m._pwm_base =  m.rpm_to_pwm(m._rpm_target);

m.muovi(m._pwm_base);

Serial.println(m._pwm_base);

}


unsigned long prima = millis();
bool nolog = true;
void loop()
{ if ( (millis() - prima < 30000) or nolog )
  {

      if (m._rpm_valida)
      {
        Serial.print(m._rpm_target);
        Serial.print(" / ");
        Serial.print(m._rpm);

        Serial.print(" pwm ");
        Serial.print(m._pwm);
      
        Serial.print(" Kp = ");
        Serial.print(Kp);
        Serial.print(" Ki =");
        Serial.println(Ki);
      }
      else
        Serial.println("----");

      delay(100);
  }

  else{
    //stampo log :
    for (int i =0 ; i<MAX_LOG_PID ; i++){
      Serial.print(" time= ");
      Serial.print(i*INTERVALLO_CAMPIONAMENTO_RPM);
      
      Serial.print(" ms  rpm target ");
      Serial.print(m._rpm_target);
      Serial.print(" rpm in input al PID  ");
      Serial.print(log_pid_rpm_in_input[i]);
      
      Serial.print(" output = ");
      Serial.print(log_pid_output[i]);
        Serial.print("   Kp = ");
        Serial.print(Kp);
        Serial.print(" Ki =");
        Serial.println(Ki);
      delay(300);
      
    }

  }
}

// int pwm = 120;
// void loop()
// {
//   if (pwm <= 250)
//   {
//     int c = 0;
//     while (c < 4)
//     {
//       if (m._rpm_valida)
//       {
//         Serial.print(m._rpm_target);
//         Serial.print(" / ");
//         Serial.print(m._rpm);

//         Serial.print(" pwm");
//         Serial.println(m._pwm);
//       }
//       else
//         Serial.println("----");
//       delay(100);
//       c++ ;
//     };
//     Serial.println();
//     pwm += 10;
//     m.muovi(pwm);
//   }
// }


