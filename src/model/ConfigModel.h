#ifndef CONFIG_MODEL_H
#define CONFIG_MODEL_H

#include <Arduino.h>

struct WifiConfig{
    String ssid;
    String password;
};

// struct MQTTConfig{
//     String host;
//     int port;
//     String username;
//     String password;
// };

#endif