#include "controller.h"

Motore Controller::motori[] = {Motore(PIN_MOT_AD1, PIN_MOT_AD2,PIN_PWM_AD, PIN_ENC_AD1, PIN_ENC_AD2),
                               Motore(PIN_MOT_PD1, PIN_MOT_PD2,PIN_PWM_PD, PIN_ENC_PD1, PIN_ENC_PD2),
                               Motore(PIN_MOT_PS1, PIN_MOT_PS2,PIN_PWM_PS, PIN_ENC_PS1, PIN_ENC_PS2),
                               Motore(PIN_MOT_AS1, PIN_MOT_AS2,PIN_PWM_AS, PIN_ENC_AS1, PIN_ENC_AS2)};

Motore &Controller::_mot_ant_dx = motori[0];
Motore &Controller::_mot_pos_dx = motori[1];
Motore &Controller::_mot_pos_sx = motori[2];
Motore &Controller::_mot_ant_sx = motori[3];

//TODO: spostare PID nei motori in modo da rendere private _rpm e _rpm_target 
QuickPID Controller::pids[] = {QuickPID(&Controller::_mot_ant_dx._rpm, &Controller::output_pid_AD, &Controller::_mot_ant_dx._rpm_target),
                               QuickPID(&Controller::_mot_pos_dx._rpm, &Controller::output_pid_PD, &Controller::_mot_pos_dx._rpm_target),
                               QuickPID(&Controller::_mot_pos_sx._rpm, &Controller::output_pid_PS, &Controller::_mot_pos_sx._rpm_target),
                               QuickPID(&Controller::_mot_ant_sx._rpm, &Controller::output_pid_AS, &Controller::_mot_ant_sx._rpm_target)};

QuickPID &Controller::pid_AD=pids[0];
QuickPID &Controller::pid_PD=pids[1];
QuickPID &Controller::pid_PS=pids[2];
QuickPID &Controller::pid_AS=pids[3];


float Controller::output_pids[]={0,0,0,0};
float &Controller::output_pid_AD=output_pids[0];
float &Controller::output_pid_PD=output_pids[1];
float &Controller::output_pid_PS=output_pids[2];
float &Controller::output_pid_AS=output_pids[3];


HardwareTimer *Controller::Timer_per_pid =nullptr;



Controller::Controller() 
{

};

void Controller::init(){
  for (int i=0;i<4;i++) motori[i].stop();
 

   // TODO: i pin degli encoder sono deginiti INPUT_PULLUP nei Motori: e' il caso di spostare qui?
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), ISR_encoder_Motore_AD, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_PD1), ISR_encoder_Motore_PD, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_PS1), ISR_encoder_Motore_PS, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore_AS, RISING);


   // SETTAGGIO PID PER MOTORI // pid_AD.SetAntiWindupMode(QuickPID::iAwMode::iAwClamp);
   for (int i=0; i<4 ; i++){
      pids[i].SetSampleTimeUs(INTERVALLO_CAMPIONAMENTO_PID * 1000);
      pids[i].SetOutputLimits(-255, 255);
      pids[i].SetMode(QuickPID::Control::timer);
   }
   pids[0].SetTunings(0.80, 0.3, 0.0); // Kp, Ki, Kd
   pids[1].SetTunings(0.80, 0.3, 0.0);       // Kp, Ki, Kd
   pids[2].SetTunings(0.80, 0.4, 0.0);       // Kp, Ki, Kd
   pids[3].SetTunings(0.80, 0.4, 0.0);       // Kp, Ki, Kd

#ifdef NO_PID
#warning PID DISABILITATO !!! Are you sure ?
#else
   // TIMER PID
   Timer_per_pid = new HardwareTimer(TIM9); // TODO: definire alias per TIM9 e spostare in robopin.h

   Timer_per_pid->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_PID, HERTZ_FORMAT);
   Timer_per_pid->attachInterrupt(aggiorna_PID_dei_quattro_motori);
   Timer_per_pid->resume();
#
#endif
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

void Controller::aggiorna_RPM_dei_quattro_motori(int deltaTms)
{ // dura circa 7 -8  us (microsecondi)
   for (int i = 0; i < 4; i++)
   {
      motori[i].aggiorna_lettura_rpm(deltaTms);

   }
}

void Controller::aggiorna_PID_dei_quattro_motori()
{  //durata max 100 u sec ( microsecondi ) //TODO: AGGIORNARE

   aggiorna_RPM_dei_quattro_motori(INTERVALLO_CAMPIONAMENTO_PID);

   for (int i = 0; i < 4; i++)
   {
      //TODO: giusto quantizzare? if (abs(motori[i].get_rpm() - motori[i].get_target_RPM())>7) //TODO: definire una costante ...
      {
         pids[i].Compute();
         int pwm_cmd = (int)output_pids[i];
         pwm_cmd = constrain(pwm_cmd, -255, 255); // TODO: ridondante?
         motori[i].muovi((int)pwm_cmd); //TODO: meglio static cast ....?
      }
   }
}

Controller controller;
