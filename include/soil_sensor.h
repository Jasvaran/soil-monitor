#pragma once

struct SoilReadings {
  int raw;
  int moisturePercent;
};

void initSoilSensor();
SoilReadings readSoil();
void printSoilReadings(const SoilReadings& soil);