#ifndef CONTROLLER_H
#define CONTROLLER_H
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

   HardwareTimer *Timer_per_rpm = new HardwareTimer(TIM5); // TODO: definire alias per TIM5 e spostare in robopin.h
};

Motore Controller::motori[] = {Motore(PIN_MOT_AD1, PIN_MOT_AD2, PIN_ENC_AD1, PIN_ENC_AD2),
                               Motore(PIN_MOT_PD1, PIN_MOT_PD2, PIN_ENC_PD1, PIN_ENC_PD2),
                               Motore(PIN_MOT_PS1, PIN_MOT_PS2, PIN_ENC_PS1, PIN_ENC_PS2),
                               Motore(PIN_MOT_AS1, PIN_MOT_AS2, PIN_ENC_AS1, PIN_ENC_AS2)};
Motore &Controller::_mot_ant_dx = motori[0];
Motore &Controller::_mot_pos_dx = motori[1];
Motore &Controller::_mot_pos_sx = motori[2];
Motore &Controller::_mot_ant_sx = motori[3];

Controller::Controller()
{ // ISR sugli encoder
  // TODO: definire getter per pin encoder nei motori trasformare in loop
  // TODO: i pin degli encoder sono deginiti INPUT_PULLUP nei Motori: e' il caso di spostare qui?

   attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), ISR_encoder_Motore_AD, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_PD1), ISR_encoder_Motore_PD, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_PS1), ISR_encoder_Motore_PS, RISING);
   attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore_AS, RISING);

   Timer_per_rpm->setOverflow(1000 / INTERVALLO_CAMPIONAMENTO_RPM, HERTZ_FORMAT);
   Timer_per_rpm->attachInterrupt(aggiorna_RPM_dei_quattro_motori);
   Timer_per_rpm->resume();

   // TODO: e' veramente necessario?
   _mot_ant_dx.resetRPM();
   _mot_pos_dx.resetRPM();
   _mot_pos_sx.resetRPM();
   _mot_ant_sx.resetRPM();
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

#endif
