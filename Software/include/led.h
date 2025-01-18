#pragma once

class Led
{
public:
    Led();

    void begin();

    void setFiring(bool firing);
    void setCharging(bool charging);
    void setInterlock(bool interlock);
    void setError(bool error);
    void setCriticalBattery(bool battery);

    void tick();

private:

    struct State
    {
        uint8_t firing    : 1;
        uint8_t charging  : 1;
        uint8_t interlock : 1;
        uint8_t error     : 1;
        uint8_t battery   : 1;
        uint8_t down      : 1;
    } _state;

    uint32_t _tickMillis;
    int8_t _value;
};