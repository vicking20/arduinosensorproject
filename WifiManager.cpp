#include "WiFiManager.h"


WiFiManager::WiFiManager(const char* ssid, const char* password)
  : ssid(ssid), password(password) {}

void WiFiManager::begin() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

bool WiFiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

int WiFiManager::status() {
  return WiFi.status();
}
