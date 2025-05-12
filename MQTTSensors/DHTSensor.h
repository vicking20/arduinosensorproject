#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <dht11.h>

class DHTSensor {
public:
    DHTSensor(uint8_t pin);
    void begin();
    void readValues();
    float getTemperature();
    float getHumidity();
private:
    dht11 DHT11;
    float temperature;
    float humidity;
    uint8_t pin;
};

#endif
