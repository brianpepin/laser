#include <Arduino.h>
#include <SPI.h>
#include "ADC104S021.h"

//=------------------------------------------------------
// ADC Protocol Definitions
//=------------------------------------------------------

union ADC_COMMAND
{
    struct
    {
        uint16_t Unused1 : 8;
        uint16_t Unused2 : 3;
        uint16_t Address : 3;
        uint16_t Unused3 : 2;
    } s;
    uint16_t v;
};

union ADC_DATA
{
    struct
    {
        uint16_t Unused1 : 2;
        uint16_t Data    : 10;
        uint16_t Unused2 : 4;
    } s;
    uint16_t v;    
};

ADC104S021::ADC104S021(uint8_t csPin) :
    _cs(csPin)
{
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
}

uint16_t ADC104S021::readValue(uint8_t channel)
{
    ADC_COMMAND cmd = {};
    cmd.s.Address = channel;

    SPISettings spi(1000000, MSBFIRST, SPI_MODE0);
    SPI.beginTransaction(spi);
    digitalWrite(_cs, LOW);

    ADC_DATA data;

    // First reading is garbage so read a second
    // to let it settle.

    for (uint8_t i = 0; i < 2; i++)
    {
        data.v = SPI.transfer16(cmd.v);
    }

    digitalWrite(_cs, HIGH);
    SPI.endTransaction();

    return data.s.Data;
}
