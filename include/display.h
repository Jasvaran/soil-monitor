#pragma once
#include "env_sensor.h"
#include "soil_sensor.h"

void initDisplay();
void displayDashboard(const Readings& r, const SoilReadings& soil);
void showDisplayError(const char* message);