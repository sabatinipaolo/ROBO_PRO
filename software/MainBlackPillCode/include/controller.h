#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QuickPID.h>
#include "motori.h"

class Controller
{
public:
   Controller();

   static Motore motori[];
   static Motore &_mot_ant_dx; // alias per motore anteriore destro
   static Motore &_mot_pos_dx; // alias per motore posteriore destro
   static Motore &_mot_pos_sx; // alias per motore posteriore sinistro
   static Motore &_mot_ant_sx; // alias per motore anteriore sinistro

   // 4 ISR static
   static void ISR_encoder_Motore_AD();
   static void ISR_encoder_Motore_PD();
   static void ISR_encoder_Motore_PS();
   static void ISR_encoder_Motore_AS();

   static void aggiorna_RPM_dei_quattro_motori();
   static void aggiorna_PID_dei_quattro_motori();

   static void computa_AD();

   HardwareTimer *Timer_per_rpm = new HardwareTimer(TIM5); // TODO: definire alias per TIM5 e spostare in robopin.h
   HardwareTimer *Timer_per_pid = new HardwareTimer(TIM9); // TODO: definire alias per TIM9 e spostare in robopin.h


   static float output_pid_AD;
   static float output_pid_PD;
   static float output_pid_PS;
   static float output_pid_AS;
   
   static QuickPID pid_AD;
   static QuickPID pid_PD;
   static QuickPID pid_PS;
   static QuickPID pid_AS;

#ifdef LOGGA_RPM

   static float m_AD_log_rpm[1024];
   static float m_PD_log_rpm[1024];
   static float m_PS_log_rpm[1024];
   static float m_AS_log_rpm[1024];
 
   static float m_AD_log_otuput_pid[1024];
   static float m_PD_log_otuput_pid[1024];
   static float m_PS_log_otuput_pid[1024];
   static float m_AS_log_otuput_pid[1024];

   static int indice_log;


#endif

private:
   static void calcola_nuova_rpm(Motore & m);




};


Motore Controller::motori[] = {Motore(PIN_MOT_AD1, PIN_MOT_AD2, PIN_ENC_AD1, PIN_ENC_AD2),
                               Motore(PIN_MOT_PD1, PIN_MOT_PD2, PIN_ENC_PD1, PIN_ENC_PD2),
                               Motore(PIN_MOT_PS1, PIN_MOT_PS2, PIN_ENC_PS1, PIN_ENC_PS2),
                               Motore(PIN_MOT_AS1, PIN_MOT_AS2, PIN_ENC_AS1, PIN_ENC_AS2)};
Motore &Controller::_mot_ant_dx = motori[0];
Motore &Controller::_mot_pos_dx = motori[1];
Motore &Controller::_mot_pos_sx = motori[2];
Motore &Controller::_mot_ant_sx = motori[3];

float Controller::output_pid_AD=0;
float Controller::output_pid_PD=0;
float Controller::output_pid_PS=0;
float Controller::output_pid_AS=0;

QuickPID Controller::pid_AD(&Controller::_mot_ant_dx._rpm,&Controller::output_pid_AD,&Controller::_mot_ant_dx._rpm_target);
QuickPID Controller::pid_PD(&Controller::_mot_pos_dx._rpm,&Controller::output_pid_PD,&Controller::_mot_pos_dx._rpm_target);
QuickPID Controller::pid_PS(&Controller::_mot_pos_sx._rpm,&Controller::output_pid_PS,&Controller::_mot_pos_sx._rpm_target);
QuickPID Controller::pid_AS(&Controller::_mot_ant_sx._rpm,&Controller::output_pid_AS,&Controller::_mot_ant_sx._rpm_target);

#ifdef LOGGA_RPM
   Controller::indice_log =0;
#endif


Controller::Controller() 
{ // ISR sugli encoder
  // TODO: definire getter per pin encoder nei motori trasformare in loop
  // TODO: i pin degli encoder sono deginiti INPUT_PULLUP nei Motori: e' il caso di spostare qui?

   attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), ISR_encoder_Motore_AD, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_PD1), ISR_encoder_Motore_PD, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_PS1), ISR_encoder_Motore_PS, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore_AS, RISING);
   // TODO: e' veramente necessario?
   _mot_ant_dx.resetRPM();
   _mot_pos_dx.resetRPM();
   _mot_pos_sx.resetRPM();
   _mot_ant_sx.resetRPM();


   Timer_per_rpm->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_RPM, HERTZ_FORMAT);
   Timer_per_rpm->attachInterrupt(aggiorna_RPM_dei_quattro_motori);
   Timer_per_rpm->resume();

   Timer_per_pid->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_RPM, HERTZ_FORMAT);
   Timer_per_pid->attachInterrupt(aggiorna_PID_dei_quattro_motori);
   //Timer_per_pid->resume();

   pid_AD.SetSampleTimeUs(INTERVALLO_CAMPIONAMENTO_RPM * 1000);
   pid_AD.SetOutputLimits(0, 255);
   
   //pid_AD.SetAntiWindupMode(QuickPID::iAwMode::iAwClamp);
   
   pid_AD.SetMode(QuickPID::Control::timer);
   pid_AD.SetTunings(0.01, 0.00, 0.0); // Kp, Ki, Kd
   pid_AD.SetProportionalMode(QuickPID::pMode::pOnError);

};

void Controller::aggiorna_RPM_dei_quattro_motori()
{ // dura circa 2 - 6 us (microsecondi)
   for (int i = 0; i < 4; i++)
   {
      motori[i].aggiorna_rpm();
   }
}

void Controller::ISR_encoder_Motore_AD()
{
   _mot_ant_dx.ISR_encoder();
}

void Controller::ISR_encoder_Motore_PD()
{
   _mot_pos_dx.ISR_encoder();
}

void Controller::ISR_encoder_Motore_PS()
{
   _mot_pos_sx.ISR_encoder();
}

void Controller::ISR_encoder_Motore_AS()
{
   _mot_ant_sx.ISR_encoder();
}


void Controller::aggiorna_PID_dei_quattro_motori(){


   if (_mot_ant_dx._rpm_valida)
   {

#ifdef LOGGA_RPM
      m_AD_log_rpm[indice_log]=_mot_ant_dx._rpm;
      m_PD_log_rpm[indice_log]=_mot_pos_dx._rpm;
      m_PS_log_rpm[indice_log]=_mot_pos_sx._rpm;
      m_AS_log_rpm[indice_log]=_mot_ant_sx._rpm;

      float m_AD_log_otuput_pid[indice_log]=output_pid_AD;
      float m_PD_log_otuput_pid[indice_log]=output_pid_PD;
      float m_PS_log_otuput_pid[indice_log]=output_pid_PS;
      float m_AS_log_otuput_pid[indice_log]=output_pid_AS;

      if (output_pid_AD++ == 1024)output_pid_AD=0;
      if (output_pid_PD++ == 1024)output_pid_PD=0;
      if (output_pid_PS++ == 1024)output_pid_PS=0;
      if (output_pid_AS++ == 1024)output_pid_AS=0;

#endif

      Controller::pid_AD.Compute();
      float pwm_base = _mot_ant_dx.rpm_to_pwm(_mot_ant_dx._rpm_target); // TODO: creare attributo per non calcolarlo ogni volta
      float pwm_cmd = _mot_ant_dx._pwm + output_pid_AD;
      //float pwm_cmd = output_pid_AD;
      pwm_cmd = constrain(pwm_cmd, 0, 255);
      _mot_ant_dx.muovi((int)pwm_cmd);
   }

// float pwm_base = _mot_ant_dx(targetRPM);
// float pwm_cmd  = pwm_base + pid_output;
// pwm_cmd = constrain(pwm_cmd, 0, 255);

//pid_PD
//pid_PS
//pid_AS

}

// void Controller::computa_AD(){
//    pid_AD.Compute();
// }

// void Controller::ISR_encoder_Motore_AD()
// {
//       calcola_nuova_rpm(_mot_ant_dx);
// }

// void Controller::ISR_encoder_Motore_PD()
// {
//    calcola_nuova_rpm(_mot_pos_dx);
// }

// void Controller::ISR_encoder_Motore_PS()
// {
//    calcola_nuova_rpm(_mot_pos_sx);
// }

// void Controller::ISR_encoder_Motore_AS()
// {
//    calcola_nuova_rpm(_mot_ant_sx);
// }

#endif
