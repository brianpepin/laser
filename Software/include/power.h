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
    Status getStatus();

    #ifdef ENABLE_SIMULATION
    void setSimulation(const Status* simulatedStatus);
    #endif

private:

    constexpr static float _filterAlpha = .9;

    ADC104S021 _adc;
    uint16_t _powerReading;

    #ifdef ENABLE_SIMULATION
    const Status* _simulatedStatus = nullptr;
    #endif
};
