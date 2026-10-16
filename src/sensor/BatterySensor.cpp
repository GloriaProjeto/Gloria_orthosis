#include "./BatterySensor.h"
#include <Arduino.h>

void BatterySensor::begin() {
    pinMode(pin, INPUT);
    analogReadResolution(12);
    analogSetPinAttenuation(pin, ADC_11db);
}

int BatterySensor::readBatteryPercentage() {
    if (voltageDividerRatio <= 0.0f) {
        return -1;
    }

    constexpr int sampleCount = 10;
    uint32_t adcMillivolts = 0;

    for (int sample = 0; sample < sampleCount; sample++) {
        adcMillivolts += analogReadMilliVolts(pin);
    }

    float adcVoltage = (adcMillivolts / static_cast<float>(sampleCount)) / 1000.0f;
    float batteryVoltage = adcVoltage * voltageDividerRatio;

    struct VoltagePoint {
        float voltage;
        int percentage;
    };
    constexpr VoltagePoint dischargeCurve[] = {
        {9.9f, 0},
        {10.2f, 2},
        {10.5f, 5},
        {10.8f, 10},
        {11.1f, 20},
        {11.4f, 40},
        {11.7f, 60},
        {12.0f, 80},
        {12.3f, 90},
        {12.6f, 100}
    };

    if (batteryVoltage <= dischargeCurve[0].voltage) {
        return 0;
    }

    constexpr size_t pointCount = sizeof(dischargeCurve) / sizeof(dischargeCurve[0]);
    for (size_t point = 1; point < pointCount; point++) {
        if (batteryVoltage <= dischargeCurve[point].voltage) {
            const VoltagePoint& lower = dischargeCurve[point - 1];
            const VoltagePoint& upper = dischargeCurve[point];
            float fraction = (batteryVoltage - lower.voltage) / (upper.voltage - lower.voltage);
            float percentage = lower.percentage + fraction * (upper.percentage - lower.percentage);
            return static_cast<int>(percentage + 0.5f);
        }
    }

    return 100;
}
