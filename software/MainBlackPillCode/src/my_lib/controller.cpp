#include "controller.h"

Motore Controller::motori[] = {Motore(PIN_MOT_AD1, PIN_MOT_AD2, PIN_ENC_AD1, PIN_ENC_AD2),
                               Motore(PIN_MOT_PD1, PIN_MOT_PD2, PIN_ENC_PD1, PIN_ENC_PD2),
                               Motore(PIN_MOT_PS1, PIN_MOT_PS2, PIN_ENC_PS1, PIN_ENC_PS2),
                               Motore(PIN_MOT_AS1, PIN_MOT_AS2, PIN_ENC_AS1, PIN_ENC_AS2)};

Motore &Controller::_mot_ant_dx = motori[0];
Motore &Controller::_mot_pos_dx = motori[1];
Motore &Controller::_mot_pos_sx = motori[2];
Motore &Controller::_mot_ant_sx = motori[3];

QuickPID Controller::pids[] = {QuickPID(&Controller::_mot_ant_dx._rpm, &Controller::output_pid_AD, &Controller::_mot_ant_dx._rpm_target),
                               QuickPID(&Controller::_mot_pos_dx._rpm, &Controller::output_pid_PD, &Controller::_mot_pos_dx._rpm_target),
                               QuickPID(&Controller::_mot_pos_sx._rpm, &Controller::output_pid_PS, &Controller::_mot_pos_sx._rpm_target),
                               QuickPID(&Controller::_mot_ant_sx._rpm, &Controller::output_pid_AS, &Controller::_mot_ant_sx._rpm_target)};

QuickPID &Controller::pid_AD=pids[0];
QuickPID &Controller::pid_PD=pids[1];
QuickPID &Controller::pid_PS=pids[2];
QuickPID &Controller::pid_AS=pids[3];


float Controller::output_pid_AD=0;
float Controller::output_pid_PD=0;
float Controller::output_pid_PS=0;
float Controller::output_pid_AS=0;


HardwareTimer *Controller::Timer_per_rpm =nullptr;
HardwareTimer *Controller::Timer_per_pid =nullptr;



Controller::Controller() 
{

};

void Controller::init(){
  
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
   
   // TIMER RPM
   Timer_per_rpm = new HardwareTimer(TIM5); // TODO: definire alias per TIM5 e spostare in robopin.h

   Timer_per_rpm->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_RPM, HERTZ_FORMAT);
   Timer_per_rpm->attachInterrupt(aggiorna_RPM_dei_quattro_motori);
   Timer_per_rpm->resume();

   // SETTAGGIO PID PER MOTORI // pid_AD.SetAntiWindupMode(QuickPID::iAwMode::iAwClamp);
   for (int i=0; i<4 ; i++){
      pids[i].SetSampleTimeUs(INTERVALLO_CAMPIONAMENTO_RPM * 1000);
      pids[i].SetOutputLimits(-50, 50);
      pids[i].SetMode(QuickPID::Control::timer);
      pids[i].SetTunings(1.9, 0.1, 0.0); // Kp, Ki, Kd
      pids[i].SetProportionalMode(QuickPID::pMode::pOnError);
   }

   // TIMER PID
   Timer_per_pid = new HardwareTimer(TIM11); // TODO: definire alias per TIM9 e spostare in robopin.h

   Timer_per_pid->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_RPM, HERTZ_FORMAT);
   Timer_per_pid->attachInterrupt(aggiorna_PID_dei_quattro_motori);
   Timer_per_pid->resume();
}

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

void Controller::aggiorna_PID_dei_quattro_motori()
{

//    if (_mot_ant_dx._rpm_valida)
//    {

//       pid_AD.Compute();
//       float pwm_base = _mot_ant_dx.rpm_to_pwm(_mot_ant_dx._rpm_target); // TODO: creare attributo per non calcolarlo ogni volta
//       int pwm_cmd = pwm_base + (int) output_pid_AD;
//       // NO FEED int pwm_cmd = (int) output_pid_AD;
//       // float pwm_cmd = output_pid_AD;
//       pwm_cmd = constrain(pwm_cmd, -255, 255);
//       _mot_ant_dx.muovi((int)pwm_cmd);

// #ifdef LOGGA_PID
//       if ((!finito_log) and (_mot_ant_dx._rpm_target !=0 ))
//       {
//          m_AD_log_rpm[indice_log] = _mot_ant_dx._rpm;
//          m_PD_log_rpm[indice_log] = _mot_pos_dx._rpm;
//          m_PS_log_rpm[indice_log] = _mot_pos_sx._rpm;
//          m_AS_log_rpm[indice_log] = _mot_ant_sx._rpm;

//          m_AD_log_otuput_pid[indice_log] = output_pid_AD;
//          m_PD_log_otuput_pid[indice_log] = output_pid_PD;
//          m_PS_log_otuput_pid[indice_log] = output_pid_PS;
//          m_AS_log_otuput_pid[indice_log] = output_pid_AS;

//          if (indice_log++ == 1024)
//             finito_log = true;
//       }
// #endif
//    }
}

Controller controller;
