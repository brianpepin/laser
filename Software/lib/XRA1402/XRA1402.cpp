#include <Arduino.h>
#include <SPI.h>
#include "XRA1402.h"

//=------------------------------------------------------
// Protocol Definitions
//=------------------------------------------------------

#define COMMAND_GSR     0x00 /* RO GPIO State */
#define COMMAND_OCR     0x01 /* RW Output Control */
#define COMMAND_PIR     0x02 /* RW Input Polarity Inversion */
#define COMMAND_GCR     0x03 /* RW GPIO Configuration */
#define COMMAND_PUR     0x04 /* RW Input Internal Pullup Enable / Disable */
#define COMMAND_IER     0x05 /* RW Input Interrupt Enable */
#define COMMAND_TSCR    0x06 /* RW Output Three State Control */
#define COMMAND_ISR     0x07 /* R  Input Interrupt Status */
#define COMMAND_REIR    0x08 /* RW Input Rising Edge Interrupt Enable */
#define COMMAND_FEIR    0x09 /* RW Input Falling Edge Interrupt Enable */
#define COMMAND_IFR     0x0A /* RW Input Filter Enable / Disable */

#define OP_READ  1
#define OP_WRITE 0

union GPIO_COMMAND
{
    struct
    {
        uint16_t Data       : 8;
        uint16_t Reserved   : 1;
        uint16_t Command    : 6;
        uint16_t ReadWrite  : 1; // 1 == Read, 0 == Write
    } s;
    uint16_t v;
};

union GPIO_RESULT
{
    struct
    {
        uint16_t Data   : 8;
        uint16_t Unused : 8;
    } s;
    uint16_t v;
};

XRA1402::XRA1402(uint8_t csPin) :
    _cs(csPin)
{
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
}

void XRA1402::setDirection(uint8_t inputPins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_GCR;
    cmd.s.Data = inputPins;
    spiTransfer(cmd.v);
}

void XRA1402::invertPolarity(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_PIR;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

void XRA1402::setTriState(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_TSCR;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

void XRA1402::setPullups(uint8_t pullupPins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_PUR;
    cmd.s.Data = pullupPins;
    spiTransfer(cmd.v);
}

void XRA1402::setInterrupts(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_IER;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

void XRA1402::setRisingEdgeInterrupts(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_REIR;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

void XRA1402::setFallingEdgeInterrupts(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_FEIR;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

void XRA1402::enableInputFilter(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_IFR;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

uint8_t XRA1402::getInterruptState()
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_READ;
    cmd.s.Command = COMMAND_ISR;
    
    GPIO_RESULT result;
    result.v = spiTransfer(cmd.v);
    return result.s.Data;
}

uint8_t XRA1402::getPinState()
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_READ;
    cmd.s.Command = COMMAND_GSR;

    GPIO_RESULT result;
    result.v = spiTransfer(cmd.v);
    return result.s.Data;
}

void XRA1402::setPinState(uint8_t pins)
{
    GPIO_COMMAND cmd{};
    cmd.s.ReadWrite = OP_WRITE;
    cmd.s.Command = COMMAND_OCR;
    cmd.s.Data = pins;
    spiTransfer(cmd.v);
}

uint16_t XRA1402::spiTransfer(uint16_t value)
{
    SPISettings spi(1000000, MSBFIRST, SPI_MODE0);
    SPI.beginTransaction(spi);
    digitalWrite(_cs, LOW);
    value = SPI.transfer16(value);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    return value;
}
