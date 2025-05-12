#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H


#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"
#include "WiFiManager.h"
#include <Wire.h>

#ifdef MQTT_CLIENT_STD_FUNCTION_CALLBACK
  #include <functional>
  // Define our callback type to match the library’s std::function signature.
  typedef std::function<void(MqttClient *client, int messageSize)> MessageCallbackType;
#else
  // Otherwise, use a simple function pointer taking an int.
  typedef void (*MessageCallbackType)(int);
#endif


class MQTTManager {
public:
  MQTTManager(const char* broker, int port, WiFiClient& wifiClient);
  void begin();
  void poll();
  void publish(const char* topic, const char* payload);

  void onMessage(MessageCallbackType callback);
  int subscribe(const char* topic);
  String messageTopic();
  int available();
  int read();
  int parseMessage();
private:
  MqttClient mqttClient;
  const char* broker;
  int port;
};

#endif
