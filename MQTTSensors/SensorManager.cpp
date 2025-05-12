#include "SensorManager.h"

SensorManager::SensorManager()
  : dht(4) {}

void SensorManager::begin() {
  // Initialize other sensors
}

void SensorManager::readSensors() {
  dht.readValues();
  // Read other sensors
}

float SensorManager::getTemperature() {
  return dht.getTemperature();
}

float SensorManager::getHumidity() {
  return dht.getHumidity();
}

String SensorManager::getAllSensorData() {
    // Allocate a JSON document with enough capacity
    // You can calculate the size needed or use a dynamic allocator
    // For simplicity, we'll use a static size
    JSONVar doc;

    // Populate the JSON document
    doc["humidity"] = getHumidity();
    doc["temperature"] = getTemperature();

    // Serialize JSON to a string
    String jsonString = JSON.stringify(doc);

    return jsonString;
}
