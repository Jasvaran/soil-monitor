#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>

Adafruit_BME280 bme;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

struct Readings {
  float temperature;
  float pressure;
  float humidity;
};

void initI2C() {
  Wire.begin(21, 22); // SDA, SCL
}

void initDisplay() {
  u8g2.setI2CAddress(0x3C << 1); // U8g2 expects 8-bit address
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 12, "Starting...");
  u8g2.sendBuffer();
}

bool initBME280() {
  if (!bme.begin(0x76)) {
    if (!bme.begin(0x77)) {
      return false;
    }
  }

  Serial.print("BME280 Chip ID: 0x");
  Serial.println(bme.sensorID(), HEX);

  // Set to forced mode - we'll manually trigger measurements
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X2,   // temperature
                  Adafruit_BME280::SAMPLING_X2,   // pressure
                  Adafruit_BME280::SAMPLING_X2,   // humidity
                  Adafruit_BME280::FILTER_OFF,
                  Adafruit_BME280::STANDBY_MS_500);
  
  delay(500);
  return true;
}

Readings readBME280() {
  Readings r;
  
  // Take measurement and wait for completion
  bme.takeForcedMeasurement();
  delay(300);
  
  r.temperature = bme.readTemperature();
  r.pressure = bme.readPressure() / 100.0F;
  r.humidity = bme.readHumidity();
  
  return r;
}

void printReadings(const Readings& r) {
  static unsigned long lastRead = 0;
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

void displayReadings(const Readings& r) {
  char line1[24];
  char line2[24];
  char line3[24];

  snprintf(line1, sizeof(line1), "Temp: %.2f C", r.temperature);
  snprintf(line2, sizeof(line2), "Press: %.2f hPa", r.pressure);
  snprintf(line3, sizeof(line3), "Hum: %.2f %%", r.humidity);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 12, "BME280 Readings");
  u8g2.drawStr(0, 30, line1);
  u8g2.drawStr(0, 45, line2);
  u8g2.drawStr(0, 60, line3);
  u8g2.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  initI2C();
  initDisplay();

  if (!initBME280()) {
    Serial.println("BME280 init failed");
    u8g2.clearBuffer();
    u8g2.drawStr(0, 12, "BME280 failed");
    u8g2.sendBuffer();
    while (1) {
      delay(1000);
    }
  }

  Serial.println("BME280 OK");
}

void loop() {
  Readings readings = readBME280();

  printReadings(readings);
  displayReadings(readings);

  delay(3000);
}