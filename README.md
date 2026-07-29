# soil-monitor

ESP32-based plant monitoring and watering system. The project started with the idea of adding pH monitoring later, but the current implementation focuses on reading soil moisture and automatically watering a plant when the soil gets too dry.

## What it does now

The firmware currently:
- reads soil moisture using a capacitive soil sensor
- reads temperature, humidity, and pressure from a BME280 sensor
- shows the values on an OLED display
- activates a 5 V water pump when moisture drops below a configured threshold
- stops watering once the soil has recovered above a reset threshold

This means the system behaves as a simple automatic plant watering monitor rather than a full pH monitoring platform.

## Hardware

- ESP32 development board
- Capacitive soil moisture sensor
- BME280 temperature / humidity / pressure sensor
- SSD1306-compatible OLED display
- 5 V water pump with an appropriate driver circuit (relay or MOSFET)

## Wiring example

### I2C devices (BME280 + OLED)
- SDA -> GPIO21
- SCL -> GPIO22
- VCC -> 3.3 V
- GND -> GND

### Soil moisture sensor
- VCC -> 3.3 V
- GND -> GND
- AOUT -> ADC pin such as GPIO36

### Pump control
- Pump power should come from a suitable 5 V supply
- The ESP32 GPIO pin should drive a transistor, MOSFET, or relay module
- Do not connect the pump directly to an ESP32 GPIO pin

## Current behavior

The watering logic is configured in the pump controller code:
- water when moisture is below about 30%
- stop watering once moisture rises above about 40%
- run the pump for about 2 seconds per trigger

These thresholds can be adjusted in the pump controller source if you want different watering behavior.

## Build and upload

This project uses PlatformIO. From the repository root, run:

```bash
pio run
pio run -t upload
pio device monitor -b 115200
```

## Notes

- Keep the analog sensors and I2C modules powered correctly and share a common ground.
- ESP32 ADC readings can be noisy, so calibration and averaging may be needed for more reliable moisture readings.
- The original pH-monitoring idea is still a future extension, not part of the current build.

## Future ideas

Possible next steps for the project include:
- tuning the moisture thresholds for your plant
- adding a more robust pump driver and water level protection
- adding pH sensing and calibration support
- logging sensor data or sending it to a dashboard
