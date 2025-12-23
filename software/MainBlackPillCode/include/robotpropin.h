#ifndef ROBOTPROPIN_H
#define ROBOTPROPIN_H

#ifdef ARDUINO_MEGA2560
  #define PIN_MOT_AD1 2
  #define PIN_MOT_AD2 3

  #define PIN_MOT_PD1 4
  #define PIN_MOT_PD2 5

  #define PIN_MOT_PS1 6
  #define PIN_MOT_PS2 7

  #define PIN_MOT_AS1 8
  #define PIN_MOT_AS2 9
#endif

#ifdef BLACKPILL_F411CE

#define PIN_MOT_AD1 PA8    // TIM1_CH1
#define PIN_MOT_AD2 PA9    // TIM1_CH2

#define PIN_MOT_PD1 PA0    // TIM2_CH1
#define PIN_MOT_PD2 PA1    // TIM2_CH2

#define PIN_MOT_PS1 PA6    // TIM3_CH1
#define PIN_MOT_PS2 PB5    // TIM3_CH2

#define PIN_MOT_AS1 PB8    // TIM4_CH3
#define PIN_MOT_AS2 PB9    // TIM4_CH4

// Encoder
//  PC0–PC5
//  PA4, PA15
// UART
//  PA2 - PA3
// USB CDC 
//  PA10 PA11

  #define PIN_WIRE_SDA PB7 //default in wire.h (se cambi valore warning di ridefinizione)
  #define PIN_WIRE_SCL PB6 //default in wire.h (se cambi valore warning di ridefinizione)
#endif 


#endif // ROBOTPROPIN_H