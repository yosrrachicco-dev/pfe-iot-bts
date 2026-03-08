# 2-Minute Demo Scenario

1. Start stack:
   - `docker compose up --build`
2. Seed demo data:
   - `docker compose exec backend npm run seed`
3. Open frontend (`http://localhost`) and login:
   - email: `admin@pfe.local`
   - password: `admin123`
4. Open site `site001` details page.
5. Publish one high-risk telemetry sample to trigger alerts.
6. Refresh site details and show:
   - latest measurement
   - charts update
   - open alerts list
7. Resolve one alert from UI.
8. Open Mongo Express (`http://localhost:8081`) to show persisted collections.
