#ifndef HCSR04SENSOR_H
#define HCSR04SENSOR_H

#include <Arduino.h>

class HCSR04Sensor {
public:
    HCSR04Sensor(uint8_t trigPin, uint8_t echoPin);
    void begin();
    float getDistance();  // Function to return distance in cm

private:
    uint8_t trigPin;
    uint8_t echoPin;
};

#endif
