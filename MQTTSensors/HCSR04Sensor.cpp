#include "HCSR04Sensor.h"

HCSR04Sensor::HCSR04Sensor(uint8_t trigPin, uint8_t echoPin)
    : trigPin(trigPin), echoPin(echoPin) {}

void HCSR04Sensor::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float HCSR04Sensor::getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration = pulseIn(echoPin, HIGH);
    float distance = (duration * 0.0343) / 2;
    return distance;
}
