#include <Arduino.h>
#include "motori.h"

#define enc1 PB3
#define enc2 PB4


volatile int lastEncoded = 0; // Here updated value of encoder store.
volatile long encoderValue = 0; // Raw encoder value


void updateEncoder(){
  Serial.println("Interrupt encoder");
  int MSB = digitalRead(enc1); //MSB = most significant bit
  int LSB = digitalRead(enc2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;

  lastEncoded = encoded; //store this value for next time

}

  Motore motore(PIN1_MOT_ANT_DX , PIN2_MOT_ANT_DX);
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 pinMode(enc1, INPUT_PULLUP); 
  pinMode(enc2, INPUT_PULLUP);
  motore.antiorario(200);
  attachInterrupt(enc1, updateEncoder, CHANGE); 
  attachInterrupt(enc2, updateEncoder, CHANGE);
  Serial.begin(115200);


}

// the loop function runs over and over again forever
void loop() {
motore.antiorario(200);
Serial.println(encoderValue);
delay(100); 

}
