/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-toggle-led
 */

 #include <Arduino.h>


#define BUTTON_PIN PA8
int val = 0;
int previous_val;
 
int debounceDelay = 20;
 

boolean debounce(int pin)
{
  boolean state;
  boolean previousState;
  previousState = digitalRead(pin);
  for(int counter=0; counter < debounceDelay; counter++) {
    delay(1);
    state = digitalRead(pin);
    if( state != previousState) {
      counter = 0;
      previousState = state; }
  }
  return state;
}
 

void loop() {
  
  if(debounce(BUTTON_PIN)==LOW) {
    val++; //incrementa di 1 se il pulsante è premuto
    while(debounce(BUTTON_PIN)==LOW) { delay(5); }  //attendi il rilascio del pulsante
  }
  
  if(val != previous_val) {   //se val è cambiato, stampa a monitor seriale
    Serial.println(val);
    previous_val = val;
  }
}