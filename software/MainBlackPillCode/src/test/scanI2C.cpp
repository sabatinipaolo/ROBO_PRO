#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define PIN_I2C_SDA PB6
#define PIN_I2C_SCL PB7

void setup() {
  Serial.begin(115200);
  delay(5000); // Wait for Serial

  // 1. CRITICAL: Initialize I2C on the specific pins BEFORE Wire.begin()
  Wire.setSDA(PIN_I2C_SDA);
  Wire.setSCL(PIN_I2C_SCL);
  Wire.begin();

  

}

void loop() {
  // Your main code here

  delay(10000); // Wait 10 seconds before next scan
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