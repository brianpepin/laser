#include "globals.h"
#include "config.h"

// Reference range TEC board is using

constexpr uint16_t DMAX = 1024;
constexpr double VREF = 2.5;
constexpr double VCC  = 3.2;

constexpr double ADC_SLOPE =  -38.69341804089662847147074037052;
constexpr double ADC_OFFSET = 63.297770633945960932471188644148;
constexpr double DAC_SLOPE = -0.038837160973565245939104568426523;
constexpr double DAC_OFFSET = 2.4583057073783703507227630942975;
constexpr double COMP_SLOPE = 1.100323624595469255663430420712;
constexpr double COMP_OFFSET = -5.4381877022653721682847896440129;

static float convertTemp(uint16_t data)
{
    // Incoming data is referenced to VCC, not vref
    double voltage = (data * VCC) / DMAX;
    return voltage * ADC_SLOPE + ADC_OFFSET;
}

static uint16_t convertTemp(float celcius)
{
    double voltage = celcius * DAC_SLOPE + DAC_OFFSET;
    if (voltage < 0) voltage = 0;
    if (voltage > VREF) voltage = VREF;

    uint16_t value = static_cast<uint16_t>(voltage * DMAX / VREF);
    if (value >= DMAX) value = DMAX - 1;

    return value;
}

Tec::Tec() :
    _dac(Pins::Tec::CsSet),
    _adc(Pins::Tec::CsRead)
{
    _targets[0].init(Channel::Pump1);
    _targets[1].init(Channel::Pump2);
    _targets[2].init(Channel::Vanadate);
    _targets[3].init(Channel::Ktp);

    pinMode(Pins::Tec::Enable, OUTPUT);
    digitalWrite(Pins::Tec::Enable, LOW);
}

void Tec::enable(bool enable)
{
    digitalWrite(Pins::Tec::Enable, enable ? HIGH : LOW);
}

float Tec::readTemp(Channel channel)
{
    float temp = convertTemp(_adc.readValue((uint16_t)channel));
    return _targets[(uint8_t)channel].offset(temp);
}

void Tec::setTemp(Channel channel, float tempC)
{
    uint16_t tempValue = convertTemp(tempC);
    _dac.writeValue((uint8_t)channel, tempValue);
    _targets[(uint8_t)channel].recalibrate(tempC);
}

void Tec::setCurrent(Channel channel, float percent)
{
    uint16_t currentValue = static_cast<uint16_t>(DMAX * (1.1 * percent / 1.25));

    if (currentValue >= DMAX)
    {
        currentValue = DMAX - 1;
    }

    uint16_t address = ((uint16_t)channel) + 4;
    _dac.writeValue(address, currentValue);
}

Tec::Status Tec::getStatus()
{
    Status status;

    ChannelStatus* ch[] =
    {
        &status.pump1,
        &status.pump2,
        &status.vanadate,
        &status.ktp
    };

    status.ok = true;

    for (uint8_t i = 0; i < 4; i++)
    {
        float temp = convertTemp(_adc.readValue(i));
        ch[i]->ok = _targets[i].inTolerance(temp);
        ch[i]->temp = _targets[i].offset(temp);
        status.ok &= ch[i]->ok;
    }

    return status;
}

void Tec::Target::recalibrate(float setTemp)
{
    _setTemp = setTemp;
}

bool Tec::Target::inTolerance(float actualTemp)
{
    // If the TEC for this channel isn't attached
    // just say we're in tolerance
    if (actualTemp < Limits::Temperature::DisconnectLimit && !_everValid)
    {
        _out = false;
        return true;
    }

    // If we had a valid temperature read remember it, so if a cable
    // gets unplugged or we lose an NTE sensor we abort immediately.
    if (millis() > 1000)
    {
        _everValid = true;
    }

    float tolerance;

    switch (_channel)
    {
        default:
        case Channel::Pump1:
        case Channel::Pump2:
            tolerance = Tolerances::Temperature::Pump;
            break;

        case Channel::Vanadate:
            tolerance = Tolerances::Temperature::Vanadate;
            break;

        case Channel::Ktp:
            tolerance = Tolerances::Temperature::Ktp;
            break;
    }

    if (_out && abs(_setTemp - offset(actualTemp)) < (tolerance / 2.0))
    {
        _out = false;
    }

    bool inBounds = (abs(_setTemp - offset(actualTemp)) < tolerance);
    if (!inBounds)
    {
        _out = true;
    }

    return inBounds && !_out;
}

float Tec::Target::offset(float temp)
{
    return temp * COMP_SLOPE + COMP_OFFSET;
}