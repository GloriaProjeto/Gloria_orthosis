#ifndef CONFIG_CONTROLLER_H
#define CONFIG_CONTROLLER_H

#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "../model/ConfigModel.h"

class ConfigController {
private:
    Preferences preferences;

    WiFiClientSecure wifiClient;
    PubSubClient mqttClient;

    WebServer server;

    void startAccessPoint();
    void setupWebServer();

    void handleRoot();
    void handleSaveWifi();

public:
    bool begin();
    
    ConfigController();

    WifiConfig getWifiConfig();

    void saveWifiConfig(
        const String& ssid,
        const String& password
    );

    bool hasWifiConfig();

    void update();

    bool connectWifi();
    bool connectMQTT();
    bool connect();
};

#endif