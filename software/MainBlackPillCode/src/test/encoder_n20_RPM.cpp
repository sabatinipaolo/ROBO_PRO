#include <Arduino.h>
#include "motori.h"

#define ENCODER_A PA4 // INT0
#define ENCODER_B PA3
#define CPR 210         // 7 PPR × 30 gear ratio
#define SAMPLE_TIME 100 // ms


volatile long encoderCount = 0;

unsigned long lastTime = 0;
long lastCount = 0;
float rpm = 0;

Motore motoPD(PIN_MOT_PD1, PIN_MOT_PD2);


void encoderISR()
{
  // Determina la direzione usando il canale B
  if (digitalRead(ENCODER_B) == HIGH)
  {
    encoderCount++;
  }
  else
  {
    encoderCount--;
  }
}


void setup()
{ 
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR, RISING);

  Serial.begin(115200);
  delay(5000); //prendo tempo per monitor seriale  
  motoPD.orario(255);
}

// ----------------------
// LOOP
// ----------------------
void loop()
{
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= SAMPLE_TIME)
  {
    noInterrupts();
    long count = encoderCount;
    interrupts();

    long delta = count - lastCount;
    float dt = (currentTime - lastTime) / 1000.0;

    rpm = (delta / (float)CPR) * (60.0 / dt);

    lastCount = count;
    lastTime = currentTime;

    Serial.print("COUNT: ");
    Serial.println(count);
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
}

/*  7 impulsi per giro motore (?)
    30 giri motore per un giro ruota ( gear reduction 1:30)
    210 inpulsi per giro motore

    alla velocità massima 500rpm abbiamo
    210*60 = 12600 inpulsi /sec  = 12.6kHz
    periodo = 1 /12600 = 0.07936507936 milliSecondi  = 79.365079365 microSecondi





*/
