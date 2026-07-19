#include "pump_controller.h"
#include <Arduino.h>

const int PUMP_PIN = 18; // GPIO pin for water pump control
const int PUMP_ON = HIGH;
const int PUMP_OFF = LOW;
const int WATERING_THRESHOLD = 30; // Moisture percentage threshold to trigger watering
const int RESET_THRESHOLD = 40; // Moisture percentage threshold to stop watering
const unsigned long PUMP_DURATION_MS = 2000; // Duration to run the pump in milliseconds

bool wateringTriggered = false;

void initPumpController() {
    wateringTriggered = false;
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, PUMP_OFF); // Ensure pump is off at startup
}

static void pumpOn(){
  digitalWrite(PUMP_PIN, PUMP_ON);
}

static void pumpOff(){
  digitalWrite(PUMP_PIN, PUMP_OFF);
}


void waterSoilIfNeeded(const SoilReadings& soil) {
  // sensor has become dry
  if (soil.moisturePercent < WATERING_THRESHOLD && !wateringTriggered) {
    Serial.println("DRY detected, activating pump...");
    pumpOn();
    delay(PUMP_DURATION_MS);
    pumpOff();

    Serial.println("Pump OFF");
    wateringTriggered = true;
  }

  // sensor is wet again, reset the trigger
  if (soil.moisturePercent > RESET_THRESHOLD && wateringTriggered) {
    Serial.println("Soil is wet again, resetting trigger.");
    wateringTriggered = false;
  }
}