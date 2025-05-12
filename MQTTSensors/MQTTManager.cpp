#include "MQTTManager.h"


MQTTManager::MQTTManager(const char* broker, int port, WiFiClient& wifiClient)
  : broker(broker), port(port), mqttClient(wifiClient) {}

void MQTTManager::begin() {
  mqttClient.setUsernamePassword(MQTT_USER, MQTT_PASSWORD);
}

void MQTTManager::poll() {
  mqttClient.poll();
  if (!mqttClient.connect(broker, port)) {

    Serial.print("MQTT-broker not working, errorcode is=  ");
    Serial.println(mqttClient.connectError());

  } else {
    Serial.println("MQTT is online!");
    Serial.println();
  }
}

void MQTTManager::publish(const char* topic, const char* payload) {
  mqttClient.beginMessage(topic);  //Change this to your own unique topic
  mqttClient.print(payload);       //data to be send
  mqttClient.endMessage();         //end of transmit
}

// New method to register a callback for incoming messages.
void MQTTManager::onMessage(MessageCallbackType callback) {
  return mqttClient.onMessage(callback);
}

// New method to subscribe to a topic. Returns true if successful.
int MQTTManager::subscribe(const char* topic) {
  return mqttClient.subscribe(topic);
}

String MQTTManager::messageTopic(){
  return mqttClient.messageTopic();
}

int MQTTManager::available(){
  return mqttClient.available();
}

int MQTTManager::read(){
  return mqttClient.read();
}

int MQTTManager::parseMessage() {
  return mqttClient.parseMessage();
}