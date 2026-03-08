#include <WiFi.h>
#include <PubSubClient.h>
#include "Config.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long lastTelemetryMs = 0;
unsigned long lastStatusMs = 0;

float randomFloat(float minV, float maxV) {
  return minV + ((float)random(0, 10000) / 10000.0f) * (maxV - minV);
}

String isoNow() {
  unsigned long s = millis() / 1000;
  return String("1970-01-01T00:00:") + (s % 60 < 10 ? "0" : "") + String(s % 60) + "Z";
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    String clientId = String("esp32-") + DEVICE_UID;
    if (String(MQTT_USER).length() > 0) {
      mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS);
    } else {
      mqttClient.connect(clientId.c_str());
    }
    if (!mqttClient.connected()) {
      delay(1500);
    }
  }
}

void publishTelemetry() {
  String topic = String("telecom/") + SITE_ID + "/" + DEVICE_UID + "/telemetry";

  float temperature = randomFloat(20.0, 50.0);
  float humidity = randomFloat(30.0, 90.0);
  float battery = randomFloat(9.0, 13.0);
  int intrusion = random(0, 20) == 0 ? 1 : 0;

  String payload = "{";
  payload += "\"temperature\":" + String(temperature, 2) + ",";
  payload += "\"humidity\":" + String(humidity, 2) + ",";
  payload += "\"battery\":" + String(battery, 2) + ",";
  payload += "\"intrusion\":" + String(intrusion) + ",";
  payload += "\"ts\":\"" + isoNow() + "\"";
  payload += "}";

  mqttClient.publish(topic.c_str(), payload.c_str());
}

void publishStatus(bool online) {
  String topic = String("telecom/") + SITE_ID + "/" + DEVICE_UID + "/status";
  String payload = String("{\"online\":") + (online ? "true" : "false") + ",\"ts\":\"" + isoNow() + "\"}";
  mqttClient.publish(topic.c_str(), payload.c_str());
}

void setup() {
  randomSeed((uint32_t)esp_random());
  connectWiFi();
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  connectMQTT();
  publishStatus(true);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    connectMQTT();
    publishStatus(true);
  }

  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastTelemetryMs >= 10000) {
    lastTelemetryMs = now;
    publishTelemetry();
  }

  if (now - lastStatusMs >= 30000) {
    lastStatusMs = now;
    publishStatus(true);
  }
}
