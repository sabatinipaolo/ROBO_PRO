#ifndef ROBOT_H
#define ROBOT_H

#include "motori.h"
#include "robotpropin.h"



constexpr float radice2_su2 = 0.70710678118654752440084436210485;
constexpr float pi = 3.14159265358979323846;
constexpr float quarantacinque_rad = 45 * PI / 180.0f;

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

    Motore motori[4];
    Motore &_mot_ant_dx; // alias per motore anteriore destro
    Motore &_mot_pos_dx; // alias per motore posteriore destro
    Motore &_mot_pos_sx; // alias per motore posteriore sinistro
    Motore &_mot_ant_sx; // alias per motore anteriore sinistro

    void test_motori();
private:
    
};

Robot::Robot()
    : motori{Motore(PIN_MOT_AD1, PIN_MOT_AD2 ,PIN_ENC_AD1 ,PIN_ENC_AD2),
             Motore(PIN_MOT_PD1, PIN_MOT_PD2 ,PIN_ENC_PD1 ,PIN_ENC_PD2),
             Motore(PIN_MOT_PS1, PIN_MOT_PS2 ,PIN_ENC_PS1 ,PIN_ENC_PS2),
             Motore(PIN_MOT_AS1, PIN_MOT_AS2 ,PIN_ENC_AS1 ,PIN_ENC_AS2)

      },
      _mot_ant_dx(motori[0]),
      _mot_pos_dx(motori[1]),
      _mot_pos_sx(motori[2]),
      _mot_ant_sx(motori[3])

{
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
        motori[i].test_avanti_indietro(200);
    }
}

#endif // ROBOT_H