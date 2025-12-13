#include <Arduino.h>
#include "robot.h"
#include <Wire.h>
//#include <Adafruit_SSD1306.h>

Robot robot; 

void setup()
{   
    Serial.begin(9600);
    delay(1000); // Give some time to the Serial Monitor to start
    Serial.println("Setup started");

    Wire.begin(); // Join I2C bus as master
    Serial.println("I2C bus started");
    Serial.println("Initializing robot...");
    robot.inizializza();
    Serial.println("initializein robot: done");


}
void loop()
{

 delay(600);robot.trasla(0,100);
 delay(600);robot.trasla(90,100);
 delay(600);robot.trasla(180,100);
 delay(600);robot.trasla(270,100);


         delay(1000); // Wait 10 seconds before next scan
  // 2. Perform an I2C scan to debug
  Serial.println("\nScanning I2C bus...");
  byte error, address;
  int nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Device found at 0x");
      if (address<16) Serial.print("0");
      Serial.println(address,HEX);
      nDevices++;
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found. Check wiring.");
  } else {
    Serial.println("Scan complete.");
  }
}