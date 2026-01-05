#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QuickPID.h>
#include "motori.h"

class Controller
{
public:
   Controller();
   void init();

   
   static Motore motori[];
   static Motore &_mot_ant_dx; // alias per motore anteriore destro
   static Motore &_mot_pos_dx; // alias per motore posteriore destro
   static Motore &_mot_pos_sx; // alias per motore posteriore sinistro
   static Motore &_mot_ant_sx; // alias per motore anteriore sinistro
   
   static QuickPID pids[];
   static QuickPID &pid_AD;
   static QuickPID &pid_PD;
   static QuickPID &pid_PS;
   static QuickPID &pid_AS;

   static float output_pids[];

   static float &output_pid_AD;
   static float &output_pid_PD;
   static float &output_pid_PS;
   static float &output_pid_AS;


  
   // 4 ISR static
   static void ISR_encoder_Motore_AD();
   static void ISR_encoder_Motore_PD();
   static void ISR_encoder_Motore_PS();
   static void ISR_encoder_Motore_AS();

   static void aggiorna_RPM_dei_quattro_motori();
   static void aggiorna_PID_dei_quattro_motori();

   static void enable_PID();

   static void disable_PID();

   static HardwareTimer *Timer_per_rpm ;
   static HardwareTimer *Timer_per_pid ;

#ifdef LOGGA_RPM
   void stampa_log_RPM_4_motori()

   {
      for (int i_riga = 0; i_riga < dim_log_RPM; i_riga++)
      {
         Serial.print(i_riga * INTERVALLO_CAMPIONAMENTO_RPM);
         Serial.print(" ");
         for (int im = 0; im < 4; im++)
         {
            Serial.print(motori[im].log_RPM[i_riga]);
            Serial.print(" ");
         };
         Serial.println();

      }
   }

#endif
   };

   extern Controller controller;

#endif



