#pragma once

struct Readings {
  float temperature;
  float pressure;
  float humidity;
};

bool initEnvSensor();
Readings readEnvSensor();
void printEnvReadings(const Readings& r);