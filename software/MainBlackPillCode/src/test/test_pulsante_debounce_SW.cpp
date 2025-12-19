/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-toggle-led
 */

 #include <Arduino.h>
#define ACCESO LOW
#define SPENTO HIGH

#define BUTTON_PIN PA8
int val = 0;
int previous_val;
 
int debounceDelay = 20;
 

bool debounce(int pin)
{
  bool state;
  bool previousState;
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
 
void setup() {

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, SPENTO);  
    Serial.begin(115200);
  }


void loop() {
  
  if(debounce(BUTTON_PIN)==HIGH) {
    digitalWrite(LED_BUILTIN, ACCESO);
    val++; //incrementa di 1 se il pulsante è premuto
    while(debounce(BUTTON_PIN)==HIGH) {  }  //attendi il rilascio del pulsante
    digitalWrite(LED_BUILTIN, SPENTO);
  }
  
  if(val != previous_val) {   //se val è cambiato, stampa a monitor seriale
    Serial.println(val);
    previous_val = val;
  }
}