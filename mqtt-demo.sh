#!/usr/bin/env bash
set -euo pipefail

SITE_ID="SITE_ID"
DEVICE_UID="esp32-001"

TELEMETRY='{"temperature":47.1,"humidity":85.0,"battery":10.4,"intrusion":1,"ts":"2026-03-01T12:00:00.000Z"}'
STATUS='{"online":true,"ts":"2026-03-01T12:00:05.000Z"}'

mosquitto_pub -h localhost -p 1883 -t "telecom/${SITE_ID}/${DEVICE_UID}/telemetry" -m "$TELEMETRY"
mosquitto_pub -h localhost -p 1883 -t "telecom/${SITE_ID}/${DEVICE_UID}/status" -m "$STATUS"
