#ifndef ROBOT_H
#define ROBOT_H

#include "motori.h"
#include "robotpropin.h"



constexpr float radice2_su2 = 0.70710678118654752440084436210485;
constexpr float pi = 3.14159265358979323846;
constexpr float quarantacinque_rad = 45 * pi / 180.0f;

class Robot
{
public:
    Robot();
    void inizializza();
    void trasla(float alfa, int velocita);
    void stop();

    void muovi_nord(int pwm);
    void muovi_nord_est(int pwm);
    void muovi_est(int pwm);
    void muovi_sud_est(int pwm);
    void muovi_sud(int pwm);
    void muovi_sud_ovest(int pwm );
    void muovi_ovest(int pwm);
    
    void muovi_nord_ovest(int pwm);

    static void aggiorna_RPM_dei_quattro_motori();
        
    //di fatto Robot è un singleton ...
    //ma a parte questo  i motori devono essere statici per 
    //usarli dentro le 4 ISR che necessariamente devo essere static
    
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
    
    HardwareTimer *Timer_per_rpm = new HardwareTimer(TIM5);  //TODO: definire alias per TIM5 e spostare in robopin.h 
    void test_motori();
private:
};

Motore Robot::motori[] = {Motore(PIN_MOT_AD1, PIN_MOT_AD2, PIN_ENC_AD1, PIN_ENC_AD2),
                          Motore(PIN_MOT_PD1, PIN_MOT_PD2, PIN_ENC_PD1, PIN_ENC_PD2),
                          Motore(PIN_MOT_PS1, PIN_MOT_PS2, PIN_ENC_PS1, PIN_ENC_PS2),
                          Motore(PIN_MOT_AS1, PIN_MOT_AS2, PIN_ENC_AS1, PIN_ENC_AS2)};                         
Motore & Robot::_mot_ant_dx=motori[0];
Motore & Robot::_mot_pos_dx=motori[1];
Motore & Robot::_mot_pos_sx=motori[2];
Motore & Robot::_mot_ant_sx=motori[3];

Robot::Robot()
{ // ISR sugli encoder
    //TODO: definire getter per pin encoder nei motori trasformare in loop
    //TODO: i pin degli encoder sono deginiti INPUT_PULLUP nei Motori: e' il caso di spostare qui?

    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), ISR_encoder_Motore_AD, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_PD1), ISR_encoder_Motore_PD, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_PS1), ISR_encoder_Motore_PS, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore_AS, RISING);

  Timer_per_rpm->setOverflow(100, HERTZ_FORMAT); // 10 ms 
  Timer_per_rpm->attachInterrupt(aggiorna_RPM_dei_quattro_motori);
  Timer_per_rpm->resume();

  //TODO: e' veramente necessario?
  _mot_ant_dx.resetRPM();
  _mot_pos_dx.resetRPM();
  _mot_pos_sx.resetRPM();
  _mot_ant_sx.resetRPM();


    stop();
}

void Robot::inizializza()
{
    stop();

}

void Robot::trasla(float alfa, int velocita)
{   

    
    Serial.print(" Robot.trasla : alfa= ");
    Serial.print(alfa);
    Serial.print(" velocita= ");
    Serial.println(velocita);


    float alfa_rad = alfa * pi / 180.0f;
    float cosa = cos(alfa_rad + quarantacinque_rad);
    float sina = sin(alfa_rad + quarantacinque_rad);

    int vad = static_cast<int>(velocita * radice2_su2 * cosa);
    int vps = -vad;

    int vas = static_cast<int>(-velocita * radice2_su2 * sina);
    int vpd = -vas;

    _mot_ant_dx.muovi(vad);
    _mot_pos_dx.muovi(vpd);
    _mot_ant_sx.muovi(vas);
    _mot_pos_sx.muovi(vps);
}

void Robot::stop()
{
    _mot_ant_dx.stop();
    _mot_pos_dx.stop();
    _mot_ant_sx.stop();
    _mot_pos_sx.stop();
}

//            N
//       NO   |   NE
//          \   /
//     O   --   --   E
//          /   \
//       SO   |   SE
//            S  
void Robot::muovi_nord(int pwm){
    _mot_ant_dx.orario(pwm);
    _mot_pos_dx.orario(pwm);
    _mot_pos_sx.antiorario(pwm);
    _mot_ant_sx.antiorario(pwm);
    
}
void Robot::muovi_nord_est(int pwm)
{
    _mot_ant_dx.stop();
    _mot_pos_dx.orario(pwm);
    _mot_pos_sx.stop();
    _mot_ant_sx.antiorario(pwm);

}
void Robot::muovi_est(int pwm)
{
    _mot_ant_dx.antiorario(pwm);
    _mot_pos_dx.orario(pwm);
    _mot_pos_sx.orario(pwm);
    _mot_ant_sx.antiorario(pwm);

}
void Robot::muovi_sud_est(int pwm)
{
    _mot_ant_dx.antiorario(pwm);
    _mot_pos_dx.stop();
    _mot_pos_sx.orario(pwm);
    _mot_ant_sx.stop();
}
void Robot::muovi_sud(int pwm){
    _mot_ant_dx.antiorario(pwm);
    _mot_pos_dx.antiorario(pwm);
    _mot_pos_sx.orario(pwm);
    _mot_ant_sx.orario(pwm);
}
void Robot::muovi_sud_ovest(int pwm)
{
    _mot_ant_dx.stop();
    _mot_pos_dx.antiorario(pwm);
    _mot_pos_sx.stop();
    _mot_ant_sx.orario(pwm);
}
void Robot::muovi_ovest(int pwm){
    _mot_ant_dx.orario(pwm);
    _mot_pos_dx.antiorario(pwm);
    _mot_pos_sx.antiorario(pwm);
    _mot_ant_sx.orario(pwm);
}
void Robot::muovi_nord_ovest(int pwm)
{
    _mot_ant_dx.orario(pwm);
    _mot_pos_dx.stop();
    _mot_pos_sx.antiorario(pwm);
    _mot_ant_sx.stop();
}


void Robot::test_motori()
{
    for (int i = 0; i < 4; i++)
    {
        Robot::motori[i].test_avanti_indietro(200);
    }
}

void Robot::ISR_encoder_Motore_AD()
{
  _mot_ant_dx.ISR_encoder();
}

void Robot::ISR_encoder_Motore_PD()
{
  _mot_pos_dx.ISR_encoder();
}

void Robot::ISR_encoder_Motore_PS()
{
  _mot_pos_sx.ISR_encoder();
}

void Robot::ISR_encoder_Motore_AS()
{
  _mot_ant_sx.ISR_encoder();
}

void Robot::aggiorna_RPM_dei_quattro_motori()
{  //dura circa 2 - 6 us (microsecondi)
_mot_ant_dx.aggiorna_rpm();
_mot_pos_dx.aggiorna_rpm();
_mot_pos_sx.aggiorna_rpm();
_mot_ant_sx.aggiorna_rpm();

}


#endif // ROBOT_H