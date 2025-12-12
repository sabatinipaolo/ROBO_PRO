#ifndef ROBOTPROPIN_H
#define ROBOTPROPIN_H

//#define 	PB13 	
//#define 	PB14 	
//#define 	PB15 	
//#define 	PC13 	
//#define 	PC14 	
//#define 	PC15 	
//#define 	PA15 	
//#define 	PB6  	//in blackpill_f411ce è usato da I2C1_SCL
//#define 	PB7  	//in blackpill_f411ce è usato da I2C1_SDA

#define PIN1_MOT_ANT_DX	PA8  	 // TIM1_CH1
#define PIN2_MOT_ANT_DX	PA9  	 // TIM1_CH2

#define PIN1_MOT_POS_DX	PA10 	 // TIM1_CH3
#define PIN2_MOT_POS_DX	PB0  	 // TIM3_CH3 

#define PIN1_MOT_ANT_SX	PA0  	 // TIM2_CH1
#define PIN2_MOT_ANT_SX	PA1  	 // TIM2_CH2
#define PIN1_MOT_POS_SX	PA6  	 // TIM3_CH1
#define PIN2_MOT_POS_SX	PA7  	 // TIM3_CH2

//#define 	PA11 	 // USB D-  
//#define 	PA12 	 // USB D+ 

#ifdef BLACKPILL_F411CE
  #define PIN_WIRE_SDA PB7 //default in wire.h (se cambi valore warning di ridefinizione)
  #define PIN_WIRE_SCL PB6 //default in wire.h (se cambi valore warning di ridefinizione)
#endif 


#endif // ROBOTPROPIN_H