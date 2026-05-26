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

**Wiring Sanity Checks**

Before uploading code, verify your breadboard physically:
- [ ] All modules powered at 3.3V (not 5V); use the ESP32 3V3 pin or breadboard + rail.
- [ ] Common ground: ESP32 GND, all module GND pins, and breadboard - rail connected together.
- [ ] I2C bus correctly wired in parallel (not daisy-chained in series):
  - SDA from ESP32 GPIO21 -> both BME280 and OLED SDA pads (same net/wire)
  - SCL from ESP32 GPIO22 -> both BME280 and OLED SCL pads (same net/wire)
  - VCC from 3.3V -> all module VCC pads independently from the + rail
  - GND from common ground -> all module GND pads independently from the - rail
- [ ] BME280 VCC jumper set to 3.3V (if module has a selectable jumper).
- [ ] USB data cable (not charge-only) connected to the USB-to-UART port on the ESP32.

**Expected Outputs (from test sketches)**

After wiring, upload and run each test in order:

1. I2C Scanner
   - Run `src/i2c_scanner.cpp` or equivalent I2C scan.
   - Expected: `I2C device found at 0x3C` (OLED) and one of `0x76` or `0x77` (BME280).

2. OLED Display Test
   - Upload a simple U8g2 sketch that draws "Hello OLED 0x3C".
   - Expected: Text appears on the OLED screen.

3. BME280 Read Test
   - Upload BME280 sketch that reads temperature, pressure, humidity.
   - Expected: Serial output like `T: 24.5 °C  P: 1013.2 hPa  H: 45.3 %` repeating every 2 seconds.

4. Soil Sensor ADC Test (after soil sensor is wired to GPIO36)
   - Upload ADC test that reads raw analog values (0-4095).
   - Expected: A value that changes (roughly 0-4095 range) when you touch/insert the sensor probe.

If any test fails, go back and check the checklist above; most issues are wiring, VCC jumper, or USB cable.

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
