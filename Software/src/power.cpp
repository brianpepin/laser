#include "globals.h"
#include "config.h"
#include "power.h"

Power::Power() :
    _adc(Pins::Power::Cs),
    _powerReading(0)
{
}

void Power::tick()
{
    uint16_t adcValue = _adc.readValue(3);
    _powerReading = (uint16_t)((1.0 - _filterAlpha) * adcValue + _filterAlpha * _powerReading );
}

#ifdef ENABLE_SIMULATION
void Power::setSimulation(const Status* simulatedStatus)
{
    _simulatedStatus = simulatedStatus;
}
#endif

Power::Status Power::getStatus()
{
    #ifdef ENABLE_SIMULATION
    if (_simulatedStatus != nullptr)
    {
        return *_simulatedStatus;
    }
    #endif

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
    adcValue = _powerReading;
    status.adc.laserOutputPower = adcValue;

    // For output power calibration we store a power
    // and ADC value and assume p=0 when adc=0;

    if (adcValue != 0)
    {
        float cp = settings.calibration.power.output;
        float cadc = settings.calibration.power.adc;
        float slope = cp / cadc;
        status.laserOutputPower = slope * adcValue;
    }

    return status;
}

