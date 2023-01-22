#pragma once
#include "ADC104S021.h"

class Power
{
public:
    Power();

    void tick();

    float getBatteryVoltage();
    float getBatteryCurrent();
    bool isBatteryCharging();

    float getLaserOutputPower();

private:

    constexpr static uint8_t _averageCount = 64;

    ADC104S021 _adc;
    int16_t _powerAverages[_averageCount];
    uint8_t _nextPowerAverage;
};
