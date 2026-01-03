#include <Arduino.h>
#include <QuickPID.h>

#include "motori.h"

// Define Variables we'll be connecting to
float Setpoint, Input, Output;



Motore m(PIN_MOT_AS1, PIN_MOT_AS2, PIN_ENC_AS1, PIN_ENC_AS2);

static void ISR_encoder_Motore()
{
  m.ISR_encoder();
}

// Specify PID links
QuickPID myPID(&m._rpm, &Output, &Setpoint);

void setup()
{
  Serial.begin(115200);
  while (!Serial1)
    ;
  Serial.println("Starting program ");

  pinMode(PIN_ENC_AS1, INPUT_PULLUP);
  pinMode(PIN_ENC_AS2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_AS1), ISR_encoder_Motore, RISING);

  Setpoint = 350;


  float Kp = 1.0, Ki = 0.50, Kd = 0.0;
  myPID.SetTunings(Kp, Ki, Kd);

  // turn the PID on
  myPID.SetMode(QuickPID::Control::automatic);

  m.muovi(130);
  delay(10);
    m.aggiorna_lettura_rpm();
  Serial.print("iniziale rpm = ");
  Serial.print(m._rpm);
  delay(5000);
}

void loop()
{
  m.aggiorna_lettura_rpm();
  Serial.print("rpm = ");
  Serial.print(m._rpm);

  myPID.Compute();

  m.muovi((int)Output);

  Serial.print(" target =");
  Serial.print(Setpoint);

  Serial.print(" Output =");
  Serial.println(Output);

  delay(10);
}