#include "ConfigController.h"
#include "../model/ConfigModel.h"
#include <Arduino.h>
#include <WiFi.h>
#include "../../SECRETS.h"

bool ConfigController::begin() {
    wifiClient.setCACert(MQTT_ROOT_CA);
    mqttClient.setClient(wifiClient);
    return true;
}

ConfigController::ConfigController()
    : server(80) {
}

void ConfigController::saveWifiConfig(const String& ssid, const String& password) {
    preferences.begin("wifi", false);

    preferences.putString("ssid", ssid);
    preferences.putString("password", password);

    preferences.end();
}

WifiConfig ConfigController::getWifiConfig() {
    preferences.begin("wifi", true);

    WifiConfig config;
    config.ssid = preferences.getString("ssid", "");
    config.password = preferences.getString("password", "");

    preferences.end();
    return config;
}

void ConfigController::handleRoot(){
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <title>GLÓRIA - Configuração</title>
    </head>

    <body>

        <h1>GLÓRIA</h1>

        <h2>Configuração Wi-Fi</h2>

        <form action="/save" method="POST">

            <label>Nome da rede:</label>
            <br>

            <input
                type="text"
                name="ssid"
                required
            >

            <br><br>

            <label>Senha:</label>
            <br>

            <input
                type="password"
                name="password"
                required
            >

            <br><br>

            <button type="submit">
                Salvar
            </button>

        </form>

    </body>
    </html>
    )rawliteral";

    server.send(200, "text/html", html);
}

void ConfigController::setupWebServer(){
    server.on(
            "/",
            HTTP_GET,
            [this]() {
                handleRoot();
            }
        );

    server.on(
        "/save",
        HTTP_POST,
        [this]() {
            handleSaveWifi();
        }
    );
}

void ConfigController::handleSaveWifi(){
    if (
            !server.hasArg("ssid") ||
            !server.hasArg("password")
        ) {

            server.send(
                400,
                "text/plain",
                "SSID e senha sao obrigatorios."
            );

            return;
        }

        String ssid = server.arg("ssid");
        String password = server.arg("password");

        Serial.println("Nova configuracao recebida.");

        Serial.print("SSID: ");
        Serial.println(ssid);

        saveWifiConfig(
            ssid,
            password
        );

        server.send(
            200,
            "text/html",
            "<h1>Configuracao salva!</h1>"
            "<p>Reiniciando a GLORIA...</p>"
        );

        delay(1500);

        ESP.restart();
}

void ConfigController::update(){
    server.handleClient();
}

bool ConfigController::hasWifiConfig() {

    preferences.begin("wifi", true);

    String ssid = preferences.getString("ssid", "");
    String password = preferences.getString("password", "");

    preferences.end();

    return !ssid.isEmpty() && !password.isEmpty();
}

void ConfigController::startAccessPoint(){
    Serial.println("Iniciando Access Point...");

    WiFi.disconnect(true);
    delay(100);

    WiFi.mode(WIFI_AP);

    WiFi.softAP(
        "GLORIA_00000001",
        "00000001"
    );

    Serial.println("Access Point iniciado.");

    Serial.print("SSID: ");
    Serial.println("GLORIA_00000001");

    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());

    setupWebServer();

    server.begin();

    Serial.println("Servidor HTTP iniciado.");
}


bool ConfigController::connectWifi(){
    if(!hasWifiConfig()){
        Serial.println("No WiFi config found.");

        startAccessPoint();

        return false;
    }

    WifiConfig wifiConfig = getWifiConfig();

    Serial.print("Connecting to WiFi: ");
    Serial.println(wifiConfig.ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiConfig.ssid.c_str(), wifiConfig.password.c_str());

    for(int i = 0; i < 20 && WiFi.status() != WL_CONNECTED; i++){
        delay(500);
        Serial.print(".");
    }

    if(WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected.");
        return true;
    } else {
        Serial.println("\nFailed to connect to WiFi.");

        startAccessPoint();

        return false;
    }
}

bool ConfigController::connectMQTT() {
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);

    if(mqttClient.connect("gloria_esp00000001", MQTT_USERNAME, MQTT_PASSWORD)) {
        Serial.println("Connected to MQTT broker.");
        return true;
    } else {
        Serial.print("Failed to connect to MQTT broker. State: ");
        Serial.println(mqttClient.state());
        return false;
    }
}

bool ConfigController::connect() {

    if (!connectWifi()) {
        Serial.println("Nao foi possivel conectar ao Wi-Fi.");
        return false;
    }

    if (!connectMQTT()) {
        Serial.println("Nao foi possivel conectar ao MQTT.");
        return false;
    }

    Serial.println("GLORIA conectada ao Wi-Fi e MQTT!");

    return true;
}