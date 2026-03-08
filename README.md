# Firmware (ESP32)

## Files
- `esp32_monitor.ino`: Arduino sketch to publish telemetry and status.
- `Config.h.example`: template configuration.

## Setup
1. Install Arduino IDE and ESP32 board support.
2. Install libraries:
   - `PubSubClient`
3. Copy `Config.h.example` to `Config.h` and update values.
4. Flash `esp32_monitor.ino`.

## Behavior
- Publishes telemetry every 10 seconds to:
  - `telecom/{SITE_ID}/{DEVICE_UID}/telemetry`
- Publishes status every 30 seconds to:
  - `telecom/{SITE_ID}/{DEVICE_UID}/status`
- Telemetry is simulated (temperature, humidity, battery, intrusion).
