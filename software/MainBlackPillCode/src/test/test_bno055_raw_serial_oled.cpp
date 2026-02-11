#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "oled.h"
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!bno.begin()) {
    Serial.println("BNO055 non trovato!");
    while (1);
  }

  oled.begin();
  delay(1000);

  // Metti in CONFIG per cambiare modalità
  bno.setMode(OPERATION_MODE_CONFIG);
  delay(25);

  // Modalità senza magnetometro
  bno.setMode(OPERATION_MODE_NDOF_FMC_OFF);
  delay(20);

  // Usa quarzo esterno (importante)
  bno.setExtCrystalUse(true);

  Serial.println("Modalità: NDOF_FMC_OFF");
}

void loop() {

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> gyro  = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  float heading = euler.x(); //* DEG_TO_RAD;  // Heading (Z)
  float omega_z     = gyro.z();                // rad/s

  Serial.print("Heading [gradi]: ");
  Serial.print(heading, 4);
  Serial.print("   Omega Z [gradi/s]: ");
  Serial.println(omega_z, 4);

  oled.stampa4float( heading,omega_z,0.0f,0.0f);
  delay(100);  // ~10 Hz
}
