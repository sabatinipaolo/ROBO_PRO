#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define PIN_I2C_SDA PB3
#define PIN_I2C_SCL PB4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C // Common address for SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  delay(2000); // Wait for Serial

  // 1. CRITICAL: Initialize I2C on the specific pins BEFORE Wire.begin()
  Wire.setSDA(PIN_I2C_SDA);
  Wire.setSCL(PIN_I2C_SCL);
  Wire.begin();

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

  // 3. Initialize OLED if a device was found
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Halt forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hello, OLED!");
  display.display();
  Serial.println("OLED initialized.");
}

void loop() {
  // Your main code here
}