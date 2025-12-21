#ifndef ROBOTPROPIN_H
#define ROBOTPROPIN_H

#ifdef ARDUINO_MEGA2560
  #define PIN1_MOT_ANT_DX 2
  #define PIN2_MOT_ANT_DX 3

  #define PIN1_MOT_POS_DX 4
  #define PIN2_MOT_POS_DX 5

  #define PIN1_MOT_POS_SX 6
  #define PIN2_MOT_POS_SX 7

  #define PIN1_MOT_ANT_SX 8
  #define PIN2_MOT_ANT_SX 9
#endif

#ifdef BLACKPILL_F411CE

#define PIN1_MOT_ANT_DX PA2  //TIM2_CH3
#define PIN2_MOT_ANT_DX PA3  //TIM2_CH4

#define PIN1_MOT_POS_DX PA0  //TIM2_CH1
#define PIN2_MOT_POS_DX PA1  //TIM2_CH2

#define PIN1_MOT_POS_SX PB5  //TIM3_CH2
#define PIN2_MOT_POS_SX PB8  //TIM4_CH3

#define PIN1_MOT_ANT_SX PA6  //TIM3_CH1
#define PIN2_MOT_ANT_SX PA7  //TIM1_CH1N 


  #define PIN_WIRE_SDA PB7 //default in wire.h (se cambi valore warning di ridefinizione)
  #define PIN_WIRE_SCL PB6 //default in wire.h (se cambi valore warning di ridefinizione)
#endif 


#endif // ROBOTPROPIN_H