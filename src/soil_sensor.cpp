#include "soil_sensor.h"
#include <Arduino.h>

const int SOIL_PIN = 33; // GPIO pin for soil moisture sensor
const int DRY_VALUE = 2460; // ADC value for dry soil
const int WET_VALUE = 1788; // ADC value for wet soil

void initSoilSensor() {
    analogReadResolution(12); // Set ADC resolution to 12 bits
}

SoilReadings readSoil() {
  SoilReadings soil;

  long total = 0;

  for (int i = 0; i < 10; i++){
    total += analogRead(SOIL_PIN);
    delay(10);
  }
  soil.raw = total / 10;
  soil.moisturePercent = map(soil.raw, DRY_VALUE, WET_VALUE, 0, 100);
  soil.moisturePercent = constrain(soil.moisturePercent, 0, 100);

  return soil;
}

void printSoilReadings(const SoilReadings& soil){
  Serial.print("Soil Raw: ");
  Serial.print(soil.raw);
  Serial.print(" | Moisture: ");
  Serial.print(soil.moisturePercent);
  Serial.println("%");
}