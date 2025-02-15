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

void Power::setSimulation(const Status* simulatedStatus)
{
    _simulatedStatus = simulatedStatus;
}

Power::Status Power::getStatus()
{
    if (_simulatedStatus != nullptr)
    {
        return *_simulatedStatus;
    }

    Status status{};
    uint16_t adcValue;

    adcValue = _adc.readValue(1);
    status.adc.batteryVoltage = adcValue;
    status.batteryVoltage = Calibration::Battery::Voltage::Offset + (Calibration::Battery::Voltage::Slope * adcValue);

    adcValue = _adc.readValue(2);
    status.adc.batteryCurrent = adcValue;
    status.batteryCurrent = Calibration::Battery::Current::Offset + (Calibration::Battery::Current::Slope * adcValue);

    // Charge state is a logic low when charging and this is routed to an ADC channel
    adcValue = _adc.readValue(0);
    status.adc.batteryCharging = adcValue;
    status.batteryCharging = adcValue < _adc.max / 2;

    // Laser Output Power
    adcValue = 0;

    for (uint8_t idx = 0; idx < _averageCount; idx++)
    {
        adcValue += _powerAverages[idx];
    }

    adcValue /= _averageCount;
    status.adc.laserOutputPower = static_cast<uint16_t>(adcValue);

    // For output power calibration we store a power
    // and ADC value and assume p=0 when adc=0;

    if (adcValue != 0)
    {
        float cp = settings.calibration.power.value;
        float cadc = settings.calibration.power.adc;
        float slope = cp / cadc;
        status.laserOutputPower = slope * adcValue;
    }

    return status;
}

