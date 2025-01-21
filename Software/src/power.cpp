#include "globals.h"
#include "config.h"
#include "power.h"

Power::Power() :
    _adc(Pins::Power::Cs),
    _nextPowerAverage(0)
{
    memset(_powerAverages, 0, sizeof(_powerAverages));
}

void Power::tick()
{
    _powerAverages[_nextPowerAverage] = _adc.readValue(3);
    _nextPowerAverage = (_nextPowerAverage + 1) % _averageCount;
}

float Power::getBatteryVoltage()
{
    int16_t adcValue = _adc.readValue(1);
    return Calibration::Battery::Voltage::Offset + (Calibration::Battery::Voltage::Slope * adcValue);
}

float Power::getBatteryCurrent()
{
    int16_t adcValue = _adc.readValue(2);
    return Calibration::Battery::Current::Offset + (Calibration::Battery::Current::Slope * adcValue);
}

bool Power::isBatteryCharging()
{
    // Charge state is a logic low when charging and this is routed to an ADC channel
    uint16_t adcValue = _adc.readValue(0);
    return adcValue < _adc.max / 2;
}

float Power::getLaserOutputPower()
{
    int32_t adcValue = 0;

    for (uint8_t idx = 0; idx < _averageCount; idx++)
    {
        adcValue += _powerAverages[idx];
    }

    adcValue /= _averageCount;
    return Calibration::LaserMonitor::Offset + (Calibration::LaserMonitor::Slope * adcValue);
}

/*

p = m * adc + b

Given: p0, adc0, p1, adc1

p0 = m * adc0 + b
p1 = m * adc1 + b

m = p0 / adc0 - b
b = p1 - m * adc1

m = p0 / adc0 - (p1 - m * adc1)

m = p0 / adc0 - p1 + m * adc1
m * (1 - adc1) = p0 / adc0 - p1
m = (p0 / adc0 - p1) / (1 - adc1)

*/