#ifndef ROBOTPROPIN_H
#define ROBOTPROPIN_H


#define PIN1_MOT_ANT_DX PB8
#define PIN2_MOT_ANT_DX PB9

#define PIN1_MOT_POS_DX PB3
#define PIN2_MOT_POS_DX PB4

#define PIN1_MOT_POS_SX PA8
#define PIN2_MOT_POS_SX PA10

#define PIN1_MOT_ANT_SX PA2
#define PIN2_MOT_ANT_SX PA0

#ifdef BLACKPILL_F411CE
  #define PIN_WIRE_SDA PB7 //default in wire.h (se cambi valore warning di ridefinizione)
  #define PIN_WIRE_SCL PB6 //default in wire.h (se cambi valore warning di ridefinizione)
#endif 


#endif // ROBOTPROPIN_H