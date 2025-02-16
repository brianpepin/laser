#pragma once

#include <DAC108S085.h>
#include <ADC104S021.h>

class Tec
{
public:

    enum class Channel
    {
        Pump1,
        Pump2,
        Vanadate,
        Ktp
    };

    struct ChannelStatus
    {
        float temp;
        bool ok;
    };

    struct Status
    {
        bool ok;
        ChannelStatus pump1;
        ChannelStatus pump2;
        ChannelStatus vanadate;
        ChannelStatus ktp;
    };

    Tec();

    void enable(bool enable);
    void setSimulation(const Status* simulatedStatus);
    float readTemp(Channel channel);
    void setTemp(Channel channel, float tempC);
    void setCurrent(Channel channel, float percent);

    Status getStatus();

private:

    class Target
    {
    public:
        void init(Channel channel) { _channel = channel; }
        void recalibrate(float setTemp);
        bool inTolerance(float actualTemp);
        float offset(float temp);

    private:
        Channel _channel;
        float _setTemp = 0;
        bool _out = false;
        bool _everValid = false;
    };

    DAC108S085 _dac;
    ADC104S021 _adc;
    Target _targets[4];
    const Status* _simulatedStatus = nullptr;
};