# Architecture

## System Overview
```mermaid
flowchart LR
  ESP32[ESP32 Firmware] -->|MQTT telemetry/status| MOSQ[Mosquitto]
  MOSQ --> BACK[Backend Express + MQTT Subscriber]
  BACK --> MONGO[(MongoDB)]
  UI[Frontend React + Nginx] -->|HTTP /api| BACK
  ADMIN[User] --> UI
  ADMIN -->|Optional direct API| BACK
  MEXP[Mongo Express] --> MONGO
```

## Backend Internal Flow
```mermaid
sequenceDiagram
  participant D as Device
  participant M as Mosquitto
  participant B as Backend
  participant DB as MongoDB

  D->>M: telecom/{siteId}/{deviceUid}/telemetry
  M->>B: MQTT message
  B->>DB: upsert Device(status=online,lastSeen)
  B->>DB: insert Measurement
  B->>DB: check open alert by type/device
  alt no open alert
    B->>DB: insert Alert
  end
```

## Frontend
- React + Vite SPA served by Nginx.
- Nginx proxies `/api/*` to backend service (`http://backend:3000` in container network).
- JWT stored in browser localStorage.
