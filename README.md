# soil-monitor

ESP32-based soil and environmental monitor. This repository hosts firmware and notes for an ESP32 project to read soil sensors (capacitive analog), environmental data (BME280), and display values on an OLED. pH sensor support is the primary goal for the project and will be added/extended from this base.

**Hardware**
- ESP32 development board (any common ESP32 such as WROOM/WROVER)
- Capacitive analog soil moisture sensors (e.g. analog output modules)
- BME280 temperature / humidity / pressure sensor module (I2C)
- OLED display (I2C, e.g. SSD1306 128x64)
- Optional: analog pH sensor/probe with amplifier board (requires calibration)

**Wiring (example)**
- I2C (BME280 + OLED): connect both devices to the same I2C bus
	- SDA -> GPIO21
	- SCL -> GPIO22
	- VCC -> 3.3V
	- GND -> GND
	- BME280 I2C address commonly 0x76 (or 0x77)
- Capacitive soil moisture sensor (analog):
	- VCC -> 3.3V (do NOT power sensor with 5V if connecting its output to ESP32 ADC)
	- GND -> GND
	- AOUT -> ADC pin (example: GPIO36 / ADC1_CH0)
	- For multiple sensors use other ADC-capable pins (GPIO39, GPIO34, GPIO35, GPIO32, GPIO33, etc.)
- pH sensor (if used):
	- Use an amplifier/interface board that outputs 0–3.3V analog; connect output to an ADC pin
	- Calibrate with known buffer solutions; avoid direct probe wiring to ADC without appropriate circuitry

**Software / Build**
- This project uses PlatformIO. Build and flash with the PlatformIO CLI (from the repository root):

```bash
pio run
pio run -t upload
pio device monitor -b 115200
```

- Configure sensor pins and any compile-time options in `src/main.cpp` before building.
- Recommended libraries (add to `platformio.ini` under `lib_deps` as needed):
	- Adafruit BME280 Library
	- Adafruit Unified Sensor
	- U8g2 or Adafruit SSD1306 for OLED display

**Notes & tips**
- Power: keep sensors and modules at 3.3V when their outputs are connected to ESP32 ADCs.
- ADC readings on the ESP32 are non-linear and noisy; take averages, apply simple calibration curves, and use reference measurements where possible.
- pH probes require calibration (two- or three-point) and temperature compensation (BME280 can provide temp/humidity).

**Next steps**
- Implement sensor reading and display code in `src/main.cpp`.
- Add pH sensor calibration routines and example calibration data.
- Add optional logging (SD card) or network upload (MQTT/HTTP) for telemetry.

If you'd like, I can add a starting `src/main.cpp` sketch that reads one soil sensor, the BME280, and shows values on the OLED—shall I proceed?
