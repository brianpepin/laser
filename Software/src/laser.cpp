#include "globals.h"
#include "config.h"

#define RCS (.004)
#define RVD1 4640
#define RVD2 10000

Laser::Laser() :
    _driver(Pins::Laser::Cs, Pins::Laser::Reset, RCS, RVD1, RVD2),
    _state{},
    _millis(0)
{
    for (size_t idx = 0; idx < 2; idx++)
    {
        _channelState[idx] = {};
    }
}

void Laser::reset()
{
    _state.reset = _driver.reset();

    if (_state.reset)
    {
        _state.once = false;
    }
    else if (!_state.once)
    {
        Serial.println(F("\n** Error initializing MAX20096 **\n"));
        _state.once = true;
    }

    for (size_t idx = 0; idx < 2; idx++)
    {
        _channelState[idx] = {};
    }

    _millis = 0;
}

void Laser::error()
{
    Serial.println(F("\n** MAX20096 COM Error. Resetting. **\n"));
    _state.once = false;
    reset();
}

Laser::Status Laser::getStatus()
{
    MAX20096::Status driverStatus = _driver.getStatus();
    Laser::Status status;
    *((MAX20096::Status*)&status) = driverStatus;

    status.overtemp = input.getOverTemp() | driverStatus.thermalShutdown;
    status.ok = 
        _state.reset &&
        !status.overtemp &&
        !(driverStatus.errors.clock ||
         driverStatus.errors.parity ||
         driverStatus.errors.readWrite);

    return status;    
}

float Laser::getCurrent(Channel channel)
{
    switch (channel)
    {
        case Channel::Pump1:
            return _channelState[0].goal;
        case Channel::Pump2:
            return _channelState[1].goal;
        default:
            return _channelState[0].goal + _channelState[1].goal;
    }
}

float Laser::getMaxCurrent()
{
    return 
        settings.limits.maxPump1Current +
        settings.limits.maxPump2Current;
}

float Laser::getDriverMaxCurrent()
{
    return _driver.getMaxCurrent();
}

bool Laser::getEnabled(Channel channel)
{
    if (channel == Channel::Auto)
    {
        return _driver.getEnabled(0) || _driver.getEnabled(1);
    }
    else
    {
        return _driver.getEnabled(static_cast<uint8_t>(channel) - 1);
    }
}

void Laser::setCurrent(float amps, Channel channel)
{
    amps = max(amps, 0);

    switch (channel)
    {
        case Channel::Auto:
            {
                float maxAmps = getMaxCurrent();
                float channel1Percent = settings.limits.maxPump1Current / maxAmps;
                float channel2Percent = settings.limits.maxPump2Current / maxAmps;

                _channelState[0].goal = min(amps * channel1Percent, settings.limits.maxPump1Current);
                _channelState[1].goal = min(amps * channel2Percent, settings.limits.maxPump2Current);
            }
            break;

        case Channel::Pump1:
            amps = min(amps, settings.limits.maxPump1Current);
            _channelState[0].goal = amps;
            break;

        case Channel::Pump2:
            amps = min(amps, settings.limits.maxPump2Current);
            _channelState[1].goal = amps;
            break;
    }

    _millis = 0;
}

void Laser::enable(bool enable, Channel channel)
{
    if (!_state.reset)
    {
        return;
    }

    // Disable immediately.  Enable happens through tick
    // to ramp current up.

    bool changeChannel[] =
    {
        !enable || (settings.limits.maxPump1Current != 0 && (channel == Channel::Auto || channel == Channel::Pump1)),
        !enable || (settings.limits.maxPump2Current != 0 && (channel == Channel::Auto || channel == Channel::Pump2))
    };

    for (uint8_t idx = 0; idx < 2; idx++)
    {
        if (!_driver.setCurrent(idx, 0) ||
            !_driver.setEnabled(idx, enable && changeChannel[idx]))
        {
            error();
        }
        _channelState[idx].actual = 0;
    }
}

// We ramp current up in software for soft starting
// diodes.  This is done as part of the refresh tick.
void Laser::tick()
{
    uint32_t m = millis();

    if (_millis != 0 && m - _millis < Calibration::Slew::Delay)
    {
        return;
    }

    _millis = m;

    for (uint8_t idx = 0; idx < 2; idx++)
    {
        bool setCurrent = false;

        if (_channelState[idx].actual < _channelState[idx].goal)
        {
            _channelState[idx].actual += Calibration::Slew::Step;
            if (_channelState[idx].actual > _channelState[idx].goal)
            {
                _channelState[idx].actual = _channelState[idx].goal;
            }
            setCurrent = true;
        }
        else if (_channelState[idx].actual > _channelState[idx].goal)
        {
            _channelState[idx].actual = _channelState[idx].goal;
            setCurrent = true;
        }

        if (setCurrent && !_driver.setCurrent(idx, _channelState[idx].actual))
        {
            error();
        }
    }
}
