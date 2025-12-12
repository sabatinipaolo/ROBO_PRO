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
#define PIN1_MOT_ANT_DX PB8
#define PIN2_MOT_ANT_DX PB9

#define PIN1_MOT_POS_DX PB3
#define PIN2_MOT_POS_DX PB4

#define PIN1_MOT_POS_SX PA8
#define PIN2_MOT_POS_SX PA10

#define PIN1_MOT_ANT_SX PA2
#define PIN2_MOT_ANT_SX PA0


  #define PIN_WIRE_SDA PB7 //default in wire.h (se cambi valore warning di ridefinizione)
  #define PIN_WIRE_SCL PB6 //default in wire.h (se cambi valore warning di ridefinizione)
#endif 


#endif // ROBOTPROPIN_H