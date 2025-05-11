#include <Arduino.h>
#include "globals.h"
#include "led.h"
#include "config.h"
#include "macros.h"

constexpr uint32_t ERROR_CADENCE    = 500;
constexpr uint32_t CHARGE_CADENCE   = 1500;

constexpr int8_t ERROR_BRIGHT       = 120;
constexpr int8_t CHARGING_BRIGHT    = 120;
constexpr int8_t READY_BRIGHT       = 90;
constexpr int8_t READY_RING_BRIGHT  = 50;
constexpr int8_t FIRE_RING_BRIGHT   = 120;

Led::Led() :
    _state{},
    _tickMillis(0),
    _value1(0),
    _value2(0)
{
}

void Led::begin()
{
    uint8_t pins[] =
    {
        Pins::Led::Red,
        Pins::Led::Green,
        Pins::Led::Blue
    };

    for (size_t i = 0; i < ARRAYSIZE(pins); i++)
    {
        pinMode(pins[i], OUTPUT);
        analogWrite(pins[i], 0);
    }

    // Main button LED
    pinMode(Pins::Led::Fire, OUTPUT);
    pinMode(Pins::Led::Ready, OUTPUT);
    digitalWrite(Pins::Led::Fire, LOW);
    digitalWrite(Pins::Led::Ready, LOW);
}

void Led::enableFiring(bool enable)
{
    if (enable != _state.fireEnable)
    {
        _state.fireEnable = enable;
        _tickMillis = 0;
    }
}

void Led::setFiring(bool firing)
{
    if (firing != _state.firing)
    {
        _state.firing = firing;
        _tickMillis = 0;
    }
}

void Led::setCharging(bool charging)
{
    if (charging != _state.charging)
    {
        _state.charging = charging;
        _tickMillis = 0;
    }
}

void Led::setInterlock(bool interlock)
{
    if (interlock != _state.interlock)
    {
        _state.interlock = interlock;
        _tickMillis = 0;
    }
}

void Led::setError(bool error)
{
    if (error != _state.error)
    {
        _state.error = error;
        _tickMillis = 0;
    }
}

void Led::setCriticalBattery(bool battery)
{
    if (battery != _state.battery)
    {
        _state.battery = battery;
        _tickMillis = 0;
    }
}

void Led::tick()
{
    int8_t on[5]{0};

    constexpr uint32_t c_chargeStepCadence = CHARGE_CADENCE / CHARGING_BRIGHT;

    if (_state.battery && !_state.charging && _state.interlock)
    {
        // No LED
    }
    else if (_state.error)
    {
        on[0] = 1;

        uint32_t m = millis();
        if (_tickMillis == 0 ||
            _tickMillis > m ||
            (m - _tickMillis) > ERROR_CADENCE)
        {
            _value1 = (_value1 != 0) ? 0 : ERROR_BRIGHT;
            _tickMillis = m;
        }
    }
    else if (_state.charging)
    {
        on[2] = 1;

        uint32_t m = millis();

        if (_tickMillis == 0)
        {
            _value1 = CHARGING_BRIGHT;
            _state.down = true;
            _tickMillis = m;
        }
        else if (_tickMillis > m || (m - _tickMillis) > c_chargeStepCadence)
        {
            int8_t addend = _state.down ? -1 : 1;

            if (_tickMillis < m)
            {
                addend *= ((m - _tickMillis) / c_chargeStepCadence);
            }

            _value1 += addend;
            _value1 = max(0, _value1);
            _value1 = min(CHARGING_BRIGHT, _value1);

            if (_value1 == 0 || _value1 == CHARGING_BRIGHT) _state.down = !_state.down;
            _tickMillis = m;
        }
    }
    else if (!_state.interlock)
    {
        // Power adapter connected but not charging
        on[2] = 1;
        _value1 = CHARGING_BRIGHT;
        _tickMillis = 0;
    }
    else if (!_state.fireEnable)
    {
        on[1] = 1;
        _value1 = READY_BRIGHT;
        _tickMillis = 0;
    }

    if (!_state.error && _state.fireEnable)
    {
        if (_state.firing)
        {
            on[4] = 1;
            _value2 = FIRE_RING_BRIGHT;
        }
        else if (_state.interlock)
        {
            // ready state.
            on[3] = 1;
            _value2 = READY_RING_BRIGHT;
        }
    }

    analogWrite(Pins::Led::Red,   on[0] * _value1);
    analogWrite(Pins::Led::Green, on[1] * _value1);
    analogWrite(Pins::Led::Blue,  on[2] * _value1);
    analogWrite(Pins::Led::Ready, on[3] * _value2);
    analogWrite(Pins::Led::Fire,  on[4] * _value2);
}
