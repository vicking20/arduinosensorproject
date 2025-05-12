#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include "WiFiS3.h"
#include "WiFiSSLClient.h"


class WiFiManager {
public:
  WiFiManager(const char* ssid, const char* password);
  void begin();
  bool isModulePresent();
  bool isConnected();
  int connect();
  // Disconnect from WiFi
  void disconnect();
  // Get current SSID
  String getSSID();
  // Handle WiFi events (if any)
  void handle();
  // status
  int status();
private:
  WiFiClient wifi;
  const char* ssid;
  const char* password;
};

#endif
