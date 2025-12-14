#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// guarda qui: https://community.platformio.org/t/stm32f411-based-custom-pcb-i2c-debugging/48614/2
#ifdef BLACKPILL_F411CE
  #define PIN_WIRE_SDA PB7 
  #define PIN_WIRE_SCL PB6
#endif 

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial

  // 1. CRITICAL: Initialize I2C on the specific pins BEFORE Wire.begin()

  Wire.begin();

  

}

void loop() {
  // Your main code here

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