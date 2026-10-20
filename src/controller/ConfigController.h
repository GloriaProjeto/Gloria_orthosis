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

    static ConfigController* callbackInstance;
    static void mqttCallback(char* topic, byte* payload, unsigned int length);
    bool calibrationRequested = false;
    bool mqttConnectionAttempted = false;
    bool wifiConnectionAttempted = false;
    unsigned long lastMqttAttempt = 0;
    unsigned long lastWifiAttempt = 0;

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

    bool publishBattery(int percentage);
    bool consumeCalibrationRequest();
    bool isMqttConnected();
    bool hasAttemptedMqttConnection();

    bool connectWifi();
    bool connectMQTT();
    bool connect();
};

#endif