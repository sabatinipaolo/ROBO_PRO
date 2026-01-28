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

#ifdef BLACKPILL_F411CE_DRV8833

#define PIN_MOT_AD1 PA8    // TIM1_CH1
#define PIN_MOT_AD2 PA9    // TIM1_CH2

#define PIN_MOT_PD1 PA0    // TIM2_CH1
#define PIN_MOT_PD2 PA1    // TIM2_CH2

#define PIN_MOT_PS1 PA6    // TIM3_CH1
#define PIN_MOT_PS2 PB5    // TIM3_CH2

#define PIN_MOT_AS1 PB8    // TIM4_CH3
#define PIN_MOT_AS2 PB9    // TIM4_CH4

// ENCODER - AnteRiore Destro (AD)
#define PIN_ENC_AD1 PB12    
#define PIN_ENC_AD2 PB13    

// ENCODER - Posteriore Destro (PD)  
#define PIN_ENC_PD1 PB14
#define PIN_ENC_PD2 PB15

// ENCODER - Posteriore Sinistro (PS)
#define PIN_ENC_PS1 PA5    
#define PIN_ENC_PS2 PA7    

// ENCODER - AnteRiore Sinistro (AS)
#define PIN_ENC_AS1 PB0   
#define PIN_ENC_AS2 PB1   

//Seriale 
#define PIN_UART1 PA2
#define PIN_UART2 PA3
//Serial usb CDC 
#define PIN_CDC_1 PA10  
#define PIN_CDC_2 PA11


#define PIN_WIRE_SDA PB7 //default in wire.h (se cambi valore warning di ridefinizione)
#define PIN_WIRE_SCL PB6 //default in wire.h (se cambi valore warning di ridefinizione)

#endif 

#ifdef BLACKPILL_F411CE_TB6612FNG


/*************************************************
 * MOTORI – PWM + DIR (TIM1)
 *************************************************/

// ANTERIORE DESTRO
#define PIN_MOT_AD1       PB12
#define PIN_MOT_AD2       PB13
#define PIN_PWM_AD        PA8    // TIM1_CH1

// POSTERIORE DESTRO
#define PIN_MOT_PD1       PB14
#define PIN_MOT_PD2       PB15
#define PIN_PWM_PD        PA9    // TIM1_CH2

// POSTERIORE SINISTRO
#define PIN_MOT_PS1       PA15
#define PIN_MOT_PS2       PC14
#define PIN_PWM_PS        PA10   // TIM1_CH3

// ANTERIORE SINISTRO
#define PIN_MOT_AS1       PC15
#define PIN_MOT_AS2       PB0
#define PIN_PWM_AS        PB6    // TIM4_CH1


/*************************************************
 * ENCODER – HARDWARE
 *************************************************/

// Encoder AD
#define PIN_ENC_AD1       PA0    // TIM2_CH1
#define PIN_ENC_AD2       PA1    // TIM2_CH2

// Encoder PD
#define PIN_ENC_PD1       PA6    // TIM3_CH1
#define PIN_ENC_PD2       PA7    // TIM3_CH2

// Encoder AS
#define PIN_ENC_AS1       PB6    // TIM4_CH1
#define PIN_ENC_AS2       PB7    // TIM4_CH2


/*************************************************
 * ENCODER – SOFTWARE (EXTI)
 *************************************************/

// Encoder PS (ISR)
#define PIN_ENC_PS1       PB0
#define PIN_ENC_PS2       PB2


/*************************************************
 * COMUNICAZIONI
 *************************************************/

#define PIN_UART1         PA2
#define PIN_UART2         PA3

#define PIN_CDC_DM        PA11
#define PIN_CDC_DP        PA12

// I2C rimappato
#define PIN_WIRE_SCL      PB8
#define PIN_WIRE_SDA      PB9


/*************************************************
 * ANALOGICO
 *************************************************/
#define PIN_ADC_1         PA4
#endif 


#endif // ROBOTPROPIN_H