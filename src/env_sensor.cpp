#include "env_sensor.h"
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


static Adafruit_BME280 bme;

bool initEnvSensor() {
  if (!bme.begin(0x76)) {
    if (!bme.begin(0x77)) {
      Serial.println("BME280 init failed");
      return false;
    }
  }

  Serial.print("BME280 Chip ID: 0x");
  Serial.println(bme.sensorID(), HEX);

  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X2,
                  Adafruit_BME280::SAMPLING_X2,
                  Adafruit_BME280::SAMPLING_X2,
                  Adafruit_BME280::FILTER_OFF,
                  Adafruit_BME280::STANDBY_MS_500);

  delay(500); // Wait for sensor to initialize                  
  return true;
}

Readings readEnvSensor() {
  Readings r;

  bme.takeForcedMeasurement();
  delay(300);

  r.temperature = bme.readTemperature();
  r.pressure = bme.readPressure() / 100.0F;
  r.humidity = bme.readHumidity();

  return r;
}

void printEnvReadings(const Readings& r) {
  unsigned long now = millis();

  Serial.print("[");
  Serial.print(now);
  Serial.print("ms] T: ");
  Serial.print(r.temperature);
  Serial.print(" C\t");

  Serial.print("P: ");
  Serial.print(r.pressure);
  Serial.print(" hPa\t");

  Serial.print("H: ");
  Serial.print(r.humidity);
  Serial.println(" %");
}