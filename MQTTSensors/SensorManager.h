#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "DHTSensor.h"
#include <Arduino_JSON.h>
// Include other sensor headers as needed

class SensorManager {
public:
  SensorManager();
  void begin();
  void readSensors();
  float getTemperature();
  float getHumidity();
  String getAllSensorData();
  // Add getters for additional sensors
private:
  DHTSensor dht;
  float temperature;
  float humidity;
  // Add additional sensor objects and variables
};

#endif
