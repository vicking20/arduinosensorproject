#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin)
  : pin(pin) {}

void DHTSensor::begin() {
}

void DHTSensor::readValues() {
  int chk = DHT11.read(pin);
  Serial.print("Read status: ");
  Serial.println(chk);
  
  temperature = (float)DHT11.temperature;
  humidity = (float)DHT11.humidity;
}

float DHTSensor::getTemperature() {
  return temperature;
}

float DHTSensor::getHumidity() {
  return humidity;
}
