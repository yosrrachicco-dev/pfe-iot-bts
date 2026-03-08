# PFE IoT Monitoring Backend

Simple backend for IoT monitoring using Express + MongoDB + MQTT.

## Stack
- Node.js + Express
- MongoDB + Mongoose
- MQTT (Eclipse Mosquitto)
- JWT auth

## Project Structure
```txt
backend/
  src/
    app.js
    server.js
    config/
      env.js
      mongo.js
      mqtt.js
    models/
      User.js
      Site.js
      Device.js
      Measurement.js
      Alert.js
    routes/
      auth.routes.js
      sites.routes.js
      measurements.routes.js
      alerts.routes.js
    controllers/
      auth.controller.js
      sites.controller.js
      measurements.controller.js
      alerts.controller.js
    services/
      alertEngine.js
      telemetryService.js
    mqtt/
      subscriber.js
      handlers.js
    middleware/
      auth.js
      errorHandler.js
      requestLogger.js
    utils/
      logger.js
  Dockerfile
  mosquitto.conf
  package.json
```

## Run (from monorepo root)
```bash
cd ..
docker compose up --build
```

## MQTT Topics
- `telecom/{siteId}/{deviceUid}/telemetry`
- `telecom/{siteId}/{deviceUid}/status`

### Telemetry payload
```json
{"temperature":46.2,"humidity":81.5,"battery":10.8,"intrusion":1,"ts":"2026-03-01T12:00:00.000Z"}
```

### Status payload
```json
{"online":true,"ts":"2026-03-01T12:00:10.000Z"}
```

## Publish sample messages
Replace `SITE_ID` and `DEVICE_UID`.

```bash
mosquitto_pub -h localhost -p 1883 -t telecom/SITE_ID/DEVICE_UID/telemetry -m '{"temperature":46.2,"humidity":81.5,"battery":10.8,"intrusion":1,"ts":"2026-03-01T12:00:00.000Z"}'
```

```bash
mosquitto_pub -h localhost -p 1883 -t telecom/SITE_ID/DEVICE_UID/status -m '{"online":true,"ts":"2026-03-01T12:00:10.000Z"}'
```

## REST API

### Auth
Register:
```bash
curl -X POST http://localhost:3000/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"admin@example.com","password":"secret123","role":"admin"}'
```

Login:
```bash
curl -X POST http://localhost:3000/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"admin@example.com","password":"secret123"}'
```

Save token:
```bash
TOKEN="<JWT_TOKEN>"
```

### Sites CRUD
Create site:
```bash
curl -X POST http://localhost:3000/api/sites \
  -H "Authorization: Bearer $TOKEN" \
  -H "Content-Type: application/json" \
  -d '{"name":"Main Site","location":"Tunis"}'
```

Get sites:
```bash
curl http://localhost:3000/api/sites -H "Authorization: Bearer $TOKEN"
```

### Measurements
```bash
curl "http://localhost:3000/api/measurements?siteId=SITE_ID&deviceUid=device-001&from=2026-03-01T00:00:00.000Z&to=2026-03-01T23:59:59.999Z&limit=200" \
  -H "Authorization: Bearer $TOKEN"
```

### Alerts
Get alerts:
```bash
curl "http://localhost:3000/api/alerts?siteId=SITE_ID&status=open" \
  -H "Authorization: Bearer $TOKEN"
```

Resolve alert:
```bash
curl -X POST http://localhost:3000/api/alerts/ALERT_ID/resolve \
  -H "Authorization: Bearer $TOKEN"
```

## Alert rules
Thresholds (configurable in `.env`):
- `TEMP_HIGH=45`
- `HUMIDITY_HIGH=80`
- `BATTERY_LOW=11`
- `INTRUSION=1` (payload value)

Deduplication rule:
- if an **open** alert with same `type` and `deviceUid` already exists, no new one is created.
