#include <Arduino.h>
#include "SensorManager.h"
#include "LCDDisplay.h"
#include "WiFiManager.h"
#include "MQTTManager.h"
#include "WiFiSSLClient.h"
#include "HCSR04Sensor.h"

#define MQTT_SUBSCRIBER false
#define LED_PIN 8
#define BUTTON_PIN 9
#define TRIG_PIN 11
#define ECHO_PIN 12

// MQTT Broker details
const char* MQTT_SERVER = "192.168.8.152";
const int MQTT_PORT = 1883;
const char brokerTopic[] = "arduino2";
const char distanceTopic[] = "arduino2Distance";
const char commandTopic[] = "arduino2Command";
const char ledStatusTopic[] = "arduino2LedStatus";
const bool is_receiver = MQTT_SUBSCRIBER;

// stants
bool ledState = false;
int lastButtonState = HIGH;  // Using internal pull-up resistor
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second

SensorManager sensorManager;
LCDDisplay lcd;
// WiFiSSLClient wifiClient;
WiFiClient wifiClient;
WiFiManager wifiManager(SECRET_SSID, SECRET_PASS);
MQTTManager mqttCl(MQTT_SERVER, MQTT_PORT, wifiClient);
HCSR04Sensor hcsr04(TRIG_PIN, ECHO_PIN);  // Create an instance of the sensor


void setup() {
  Serial.begin(9600);

  // Initialize LED and button pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up resistor


  lcd.begin();
  lcd.writeText("Booting....");
  mqttCl.begin();
  wifiManager.begin();
  sensorManager.begin();
  hcsr04.begin();


  // set the message receive callback
  mqttCl.onMessage(onMqttMessage);
  mqttCl.subscribe(commandTopic);

  Serial.print("Subscribing to topic: ");
  Serial.println(commandTopic);
  Serial.println();

  // subscribe to a topic
  int sub_res = mqttCl.subscribe(commandTopic);
  Serial.print("Sub Res: ");
  Serial.println(sub_res);


  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic: ");
  Serial.println(brokerTopic);

  Serial.println();
}

void loop() {
  mqttCl.poll();
  unsigned long currentMillis = millis();

  int reading = digitalRead(BUTTON_PIN);
  if (reading == LOW && lastButtonState == HIGH) {
    Serial.println("Button pressed.");
    toggleLed();
  }
  lastButtonState = reading;
  // if (is_receiver) {
  // onMqttMessage();
  // } else {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    sensorManager.readSensors();
    float temp = sensorManager.getTemperature();
    float hum = sensorManager.getHumidity();
    float distance = hcsr04.getDistance();

    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("Distance: "); 
    Serial.println(distance);
    Serial.print("Hum: ");
    Serial.println(hum);

    // Display on LCD
    lcd.displayTempHumidity(temp, hum);
    lcd.writeText("Dist: " + String(distance) + " cm");

    String payload = sensorManager.getAllSensorData();
    char buffer[50];              // Allocate sufficient space
    sprintf(buffer, "%f", temp);  // Convert float to string
    // Publish to MQTT
    // mqttCl.publish(brokerTopic, payload.c_str());
    mqttCl.publish(brokerTopic, buffer);
    mqttCl.publish(distanceTopic, String(distance).c_str());

    Serial.println("Data published to MQTT");
    // delay(2000);
  }
}

void onMqttMessage(int messageSize) {
  // int messageSize = mqttCl.parseMessage();
  Serial.println("onMqttmessageCalled");

  if (messageSize) {
    // we received a message, print out the topic and contents
    Serial.println("Received a message with topic '");
    Serial.print(mqttCl.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttCl.available()) {
      Serial.print((char)mqttCl.read());
    }
    Serial.println();
    Serial.println();
  }
}

// Function to turn the LED on and update via MQTT
void turnLedOn() {
  digitalWrite(LED_PIN, HIGH);
  ledState = true;
  mqttCl.publish(ledStatusTopic, "on");
  Serial.println("LED turned ON (MQTT/button).");
}

// Function to turn the LED off and update via MQTT
void turnLedOff() {
  digitalWrite(LED_PIN, LOW);
  ledState = false;
  mqttCl.publish(ledStatusTopic, "off");
  Serial.println("LED turned OFF (MQTT/button).");
}

// Toggle the LED state and publish via MQTT
void toggleLed() {
  if (ledState) {
    turnLedOff();
  } else {
    turnLedOn();
  }
}
