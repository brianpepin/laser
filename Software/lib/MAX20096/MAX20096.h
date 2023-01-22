
#pragma once

//
// MAX20096 Dual-Channel Synchronous Buck, High-Brightness
//          LED Controller with and SPI Interface
//
// Datasheet: https://datasheets.maximintegrated.com/en/ds/MAX20096-MAX20097.pdf
//

class MAX20096
{
public:

    struct LEDStatus
    {
        float setCurrent;
        float setPwm;
        float current;
        float voltage;
        bool enabled;
        bool exception;
        bool overVoltage;
        bool overCurrent;
        bool shortDetected;
        bool openDetected;
    };

    struct Status
    {
        float dieTemp;
        bool thermalWarning;
        bool thermalShutdown;
        LEDStatus led1;
        LEDStatus led2;

        struct _Errors
        {
            uint8_t readWrite : 1;
            uint8_t parity : 1;
            uint8_t clock : 1;
            uint8_t hardwareReset : 1;
            uint8_t unused : 4;
        } errors;
        
    };

    MAX20096(uint8_t csPin, uint8_t resetPin, float rcs, uint32_t rdv1, uint32_t rdv2);

    bool reset();

    Status getStatus();

    float getMaxCurrent();

    bool getEnabled(uint8_t channel);
    float getCurrent(uint8_t channel);
    float getPWM(uint8_t channel);

    bool setEnabled(uint8_t channel, bool enabled);
    bool setCurrent(uint8_t channel, float amps);
    bool setPWM(uint8_t channel, float percent);

private:
    uint8_t _cs;
    uint8_t _reset;
    float _rcs;
    uint32_t _rvd1;
    uint32_t _rvd2;

    uint16_t spiTransfer(uint16_t value);

    void read(int cmd, uint16_t& result);
    bool write(int cmd, uint16_t data);

    float calcSetCurrent(uint8_t reading);
    float calcMonCurrent(uint8_t reading);
    float calcVoltage(uint8_t reading);
};