#include <Arduino.h>
#include <SPI.h>
#include "DAC108S085.h"

//=------------------------------------------------------
// DAC Protocol Definitions
//=------------------------------------------------------

#define OP_DAC_SET_CONFIG 1
#define OP_DAC_SET_VALUE  0
#define OP_DAC_MODE_WRM   000
#define OP_DAC_MODE_WTM   001

union DAC_COMMAND
{
    struct
    {
        uint16_t Unused     : 2;
        uint16_t Data       : 10;
        uint16_t Address    : 3;
        uint16_t Opcode     : 1;
    } s;
    uint16_t v;
};

DAC108S085::DAC108S085(uint8_t csPin) :
    _cs(csPin)
{
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
}

void DAC108S085::writeValue(uint8_t channel, uint16_t value)
{
    // Setup DAC for direct addressing
    DAC_COMMAND cmd = {};
    cmd.s.Address = OP_DAC_MODE_WTM;
    cmd.s.Opcode = OP_DAC_SET_CONFIG;
    spiTransfer(cmd.v);

    // Now set the value
    cmd.s.Address = channel;
    cmd.s.Data = value;
    cmd.s.Opcode = OP_DAC_SET_VALUE;
    spiTransfer(cmd.v);
}

uint16_t DAC108S085::spiTransfer(uint16_t value)
{
    SPISettings spi(1000000, MSBFIRST, SPI_MODE0);
    SPI.beginTransaction(spi);
    digitalWrite(_cs, LOW);
    value = SPI.transfer16(value);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    return value;
}
