#pragma once
#include "soil_sensor.h"

void initPumpController();
void waterSoilIfNeeded(const SoilReadings& soil);
