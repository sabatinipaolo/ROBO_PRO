#include <Arduino.h>
//UTILE PER CONTARE IMPULSI
volatile long enc = 0;

void isrEnc() {
  enc++;
}

void setup() {
  Serial.begin(115200);
  for (int i=0;i<=10;i++){

  delay (500);
  Serial.println(enc);
  }
  pinMode(PA4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PA4), isrEnc, CHANGE);
}

void loop() {
  Serial.println(enc);
  delay(500);
}
