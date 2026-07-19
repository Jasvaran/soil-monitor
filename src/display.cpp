#include <Arduino.h>
#include <U8g2lib.h>
#include "display.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void initDisplay() {
  u8g2.setI2CAddress(0x3C << 1); // U8g2 expects 8-bit address
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 12, "Starting...");
  u8g2.sendBuffer();
}

void displayDashboard(const Readings& r, const SoilReadings& soil){
  char line1[24];
  char line2[24];
  char line3[24];
  char line4[24];
  snprintf(line1, sizeof(line1), "Temp: %.2f C", r.temperature);
  snprintf(line2, sizeof(line2), "Press: %.2f hPa", r.pressure);
  snprintf(line3, sizeof(line3), "Hum: %.2f %%", r.humidity);
  snprintf(line4, sizeof(line4), "Soil: %d%%", soil.moisturePercent);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 10, "Env Monitor");
  u8g2.drawStr(0, 24, line1);
  u8g2.drawStr(0, 36, line2);
  u8g2.drawStr(0, 48, line3);
  u8g2.drawStr(0, 60, line4);
  u8g2.sendBuffer();
}

void showDisplayError(const char* message) {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 12, message);
    u8g2.sendBuffer();
}