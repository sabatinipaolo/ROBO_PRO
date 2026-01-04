#include <Arduino.h>
#include "motori.h"

#define CPR 210         // 7 PPR × 30 gear ratio
#define SAMPLE_TIME 100 // ms


volatile long encoderCount = 0;

unsigned long lastTime = 0;
long lastCount = 0;
float rpm = 0;

Motore mot(PIN_MOT_AD1, PIN_MOT_AD2,PIN_ENC_AD1,PIN_ENC_AD2);


void encoderISR()
{
  // Determina la direzione usando il canale B
  if (digitalRead(PIN_ENC_AD2) == HIGH)
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
  pinMode(PIN_ENC_AD1, INPUT_PULLUP);
  pinMode(PIN_ENC_AD2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_ENC_AD1), encoderISR, RISING);

  Serial.begin(115200);
  delay(5000); //prendo tempo per monitor seriale  
  mot.orario(255);
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
