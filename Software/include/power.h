#pragma once
#include "ADC104S021.h"

class Power
{
public:

    struct Status
    {
        float batteryVoltage;
        float batteryCurrent;
        float laserOutputPower;
        bool batteryCharging;

        struct Adc
        {
            uint16_t batteryVoltage;
            uint16_t batteryCurrent;
            uint16_t batteryCharging;            
            uint16_t laserOutputPower;
        } adc;
    };

    Power();
    void tick();
    void setSimulation(const Status* simulatedStatus);
    Status getStatus();

private:

    constexpr static uint8_t _averageCount = 5;

    ADC104S021 _adc;
    uint16_t _powerAverages[_averageCount];
    uint8_t _nextPowerAverage;
    const Status* _simulatedStatus = nullptr;
};
