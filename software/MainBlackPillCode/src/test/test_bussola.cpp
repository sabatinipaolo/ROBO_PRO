#include "bussola.h"

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("BUSSOLA Test");

  if (!bussola.begin()) {
    Serial.println("Failed to find BUSSOLA chip");
    while (1)
      delay(10);
  }

  Serial.println("BUSSOLA Found!");

}

void loop() {

  if (bussola.isDataReady()) {
    int16_t x, y, z;
    float gx, gy, gz;

    if (bussola.getRawMagnetic(&x, &y, &z)) {
      Serial.print("Raw - X: ");
      Serial.print(x);
      Serial.print(" Y: ");
      Serial.print(y);
      Serial.print(" Z: ");
      Serial.print(z);
      if (bussola.getGaussField(&gx, &gy, &gz)) {
        Serial.print(" | Gauss - X: ");
        Serial.print(gx, 3);
        Serial.print(" Y: ");
        Serial.print(gy, 3);
        Serial.print(" Z: ");
        Serial.println(gz, 3);
        Serial.println();

        

      } else {
        Serial.println(" | Failed to convert to Gauss");
      }

      if (bussola.isOverflow()) {
        Serial.println("WARNING: Data overflow detected!");
      }
    } else {
      Serial.println("Failed to read magnetic data");
    }
  }

  delay(1000);
}