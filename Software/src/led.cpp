#include <Arduino.h>
#include "globals.h"
#include "led.h"
#include "config.h"
#include "macros.h"

#define ERROR_CADENCE 500
#define CHARAGE_CADENCE 15

Led::Led() :
    _state{},
    _tickMillis(0),
    _value(0)
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
            _value = (_value != 0) ? 0 : 120;
            _tickMillis = m;
        }
    }
    else if (_state.firing)
    {
        on[4] = 1;
        _value = 120;
        _tickMillis = 0;
    }
    else if (_state.charging)
    {
        on[2] = 1;

        uint32_t m = millis();

        if (_tickMillis == 0)
        {
            _value = 100;
            _state.down = true;
            _tickMillis = m;
        }
        else if (_tickMillis > m || (m - _tickMillis) > CHARAGE_CADENCE)
        {
            int8_t addend = _state.down ? -1 : 1;
            _value += addend;
            if (_value == 0 || _value == 100) _state.down = !_state.down;
            _tickMillis = m;
        }
    }
    else if (_state.interlock)
    {
        // ready state.
        on[3] = 1;
        _value = 50;
        _tickMillis = 0;
    }
    else
    {
        on[2] = 1;
        _value = 100;
        _tickMillis = 0;
    }

    analogWrite(Pins::Led::Red,   on[0] * _value);
    analogWrite(Pins::Led::Green, on[1] * _value);
    analogWrite(Pins::Led::Blue,  on[2] * _value);
    analogWrite(Pins::Led::Ready, on[3] * _value);
    analogWrite(Pins::Led::Fire,  on[4] * _value);
}
