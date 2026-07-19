#include <Arduino.h>
#include <Wire.h>
#include "soil_sensor.h"
#include "pump_controller.h"
#include "env_sensor.h"
#include "display.h"

void initI2C() {
  Wire.begin(21, 22); // SDA, SCL
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  initI2C();
  initDisplay();

  if (!initEnvSensor()) {
    showDisplayError("BME280 init failed");
    Serial.println("BME280 init failed");
    while (1) {
      delay(1000);  
    }
  }

  initPumpController();

  delay(3000);
}

void loop() {
  Readings readings = readEnvSensor();
  SoilReadings soil = readSoil();

  printEnvReadings(readings);
  printSoilReadings(soil);
  displayDashboard(readings, soil);

  waterSoilIfNeeded(soil);

  delay(1000);
}