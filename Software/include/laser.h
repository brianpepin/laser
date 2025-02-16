#pragma once

#include <MAX20096.h>

class Laser
{
public:

    struct Status : MAX20096::Status
    {
        bool ok;
        bool overtemp;
    };

    enum class Channel
    {
        Auto,
        Pump1,
        Pump2
    };

    Laser();

    void reset();
    void setSimulation(const Status* simulatedStatus);
    Status getStatus();
    float getCurrent(Channel channel = Channel::Auto);
    float getMaxCurrent();
    float getDriverMaxCurrent();
    bool getEnabled(Channel channel = Channel::Auto);
    void setCurrent(float amps, Channel channel = Channel::Auto);
    void enable(bool enable, Channel channel = Channel::Auto);
    void tick();

private:

    struct State
    {
        uint8_t reset : 1;
        uint8_t once : 1;
    };

    struct ChannelState
    {
        float goal;
        float actual;
    };

    MAX20096 _driver;
    State _state;
    ChannelState _channelState[2];
    uint32_t _millis;
    const Status* _simulatedStatus = nullptr;

    void error();
};