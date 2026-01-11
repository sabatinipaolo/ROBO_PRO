#ifndef ROBOT_H
#define ROBOT_H

#include "motori.h"
#include "robotpropin.h"
#include "controller.h"
#include "oled.h"


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
  
    void test_motori();

};



Robot::Robot() 
      
{       

}

void Robot::inizializza()
{

    stop();
    controller.init();
    oled.begin();

}

void Robot::trasla(float alfa, int velocita)
{   
    



    float alfa_rad = alfa * pi / 180.0f;
    float cosa = cos(alfa_rad + quarantacinque_rad);
    float sina = sin(alfa_rad + quarantacinque_rad);

    int vad = static_cast<int>(velocita * radice2_su2 * cosa);
    int vps = -vad;

    int vas = static_cast<int>(-velocita * radice2_su2 * sina);
    int vpd = -vas;

    controller._mot_ant_dx.set_target_RPM(vad);
    controller._mot_pos_dx.set_target_RPM(vpd);
    controller._mot_ant_sx.set_target_RPM(vas);
    controller._mot_pos_sx.set_target_RPM(vps);
}

void Robot::stop()
{
    controller._mot_ant_dx.stop();
    controller._mot_pos_dx.stop();
    controller._mot_ant_sx.stop();
    controller._mot_pos_sx.stop();
}

//            N
//       NO   |   NE
//          \   /
//     O   --   --   E
//          /   \
//       SO   |   SE
//            S  
void Robot::muovi_nord(int pwm){
    controller._mot_ant_dx.orario(pwm);
    controller._mot_pos_dx.orario(pwm);
    controller._mot_pos_sx.antiorario(pwm);
    controller._mot_ant_sx.antiorario(pwm);
    
}
void Robot::muovi_nord_est(int pwm)
{
    controller._mot_ant_dx.stop();
    controller._mot_pos_dx.orario(pwm);
    controller._mot_pos_sx.stop();
    controller._mot_ant_sx.antiorario(pwm);

}
void Robot::muovi_est(int pwm)
{
    controller._mot_ant_dx.antiorario(pwm);
    controller._mot_pos_dx.orario(pwm);
    controller._mot_pos_sx.orario(pwm);
    controller._mot_ant_sx.antiorario(pwm);

}
void Robot::muovi_sud_est(int pwm)
{
    controller._mot_ant_dx.antiorario(pwm);
    controller._mot_pos_dx.stop();
    controller._mot_pos_sx.orario(pwm);
    controller._mot_ant_sx.stop();
}
void Robot::muovi_sud(int pwm){
    controller._mot_ant_dx.antiorario(pwm);
    controller._mot_pos_dx.antiorario(pwm);
    controller._mot_pos_sx.orario(pwm);
    controller._mot_ant_sx.orario(pwm);
}
void Robot::muovi_sud_ovest(int pwm)
{
    controller._mot_ant_dx.stop();
    controller._mot_pos_dx.antiorario(pwm);
    controller._mot_pos_sx.stop();
    controller._mot_ant_sx.orario(pwm);
}
void Robot::muovi_ovest(int pwm){
    controller._mot_ant_dx.orario(pwm);
    controller._mot_pos_dx.antiorario(pwm);
    controller._mot_pos_sx.antiorario(pwm);
    controller._mot_ant_sx.orario(pwm);
}
void Robot::muovi_nord_ovest(int pwm)
{
    controller._mot_ant_dx.orario(pwm);
    controller._mot_pos_dx.stop();
    controller._mot_pos_sx.antiorario(pwm);
    controller._mot_ant_sx.stop();
}


void Robot::test_motori()
{
    for (int i = 0; i < 4; i++)
    {
        Controller::motori[i].test_avanti_indietro(200);
    }
}





#endif // ROBOT_H