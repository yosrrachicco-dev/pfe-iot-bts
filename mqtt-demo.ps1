$siteId = "SITE_ID"
$deviceUid = "esp32-001"

$telemetry = '{"temperature":47.1,"humidity":85.0,"battery":10.4,"intrusion":1,"ts":"2026-03-01T12:00:00.000Z"}'
$status = '{"online":true,"ts":"2026-03-01T12:00:05.000Z"}'

mosquitto_pub -h localhost -p 1883 -t "telecom/$siteId/$deviceUid/telemetry" -m $telemetry
mosquitto_pub -h localhost -p 1883 -t "telecom/$siteId/$deviceUid/status" -m $status
