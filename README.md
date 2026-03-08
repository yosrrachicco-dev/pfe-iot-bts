# PFE IoT Monorepo

Complete PFE-ready stack with backend, frontend, firmware, and documentation.

## Requirements
- Docker Desktop only

## Start Everything
```bash
docker compose up --build
```

## Seed Demo Data
```bash
docker compose exec backend npm run seed
```

Seed creates:
- admin user: `admin@pfe.local` / `admin123`
- sample site: `site001`
- sample device: `esp32-001`

## Demo Flow
1. Open frontend and login.
2. Open `site001` details.
3. Publish MQTT samples from `docs/mqtt-demo.ps1` or `docs/mqtt-demo.sh`.
4. Watch measurements/charts/alerts update.
5. Resolve alerts in UI.

## URLs
- Frontend: `http://localhost`
- Backend API: `http://localhost:3000`
- Backend health: `http://localhost:3000/health`
- Mongo Express: `http://localhost:8081`
- MQTT broker: `localhost:1883`

## Repository Layout
- `backend/` Express + Mongo + MQTT backend
- `frontend/` React + Vite + Nginx frontend
- `firmware/` ESP32 Arduino sketch
- `docs/` architecture, demo, report, Postman, MQTT scripts
