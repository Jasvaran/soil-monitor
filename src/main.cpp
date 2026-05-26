#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL
  delay(100);
  if (!bme.begin(0x76)) { // try 0x76; if fail try 0x77
    Serial.println("BME280 not found at 0x76, try 0x77");
    if (!bme.begin(0x77)) {
      Serial.println("BME280 init failed");
      while (1) delay(1000);
    }
  }
  Serial.println("BME280 OK");
}

void loop() {
  Serial.print("T: "); Serial.print(bme.readTemperature()); Serial.print(" °C\t");
  Serial.print("P: "); Serial.print(bme.readPressure() / 100.0F); Serial.print(" hPa\t");
  Serial.print("H: "); Serial.print(bme.readHumidity()); Serial.println(" %");
  delay(2000);
}