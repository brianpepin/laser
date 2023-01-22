
#pragma once

//
// XRA1402 8 bit SPI GPIO Port Expander
//
// Datasheet: https://www.mouser.com/datasheet/2/146/XRA1402_100_092011-1889134.pdf
//

class XRA1402
{
public:

    XRA1402(uint8_t csPin);

    void setDirection(uint8_t inputPins);
    void setTriState(uint8_t pins);
    void invertPolarity(uint8_t pins);
    void setPullups(uint8_t pullupPins);
    void setInterrupts(uint8_t pins);
    void setRisingEdgeInterrupts(uint8_t pins);
    void setFallingEdgeInterrupts(uint8_t pins);
    void setPinState(uint8_t pins);
    void enableInputFilter(uint8_t pins);

    uint8_t getInterruptState();
    uint8_t getPinState();

private:
    uint8_t _cs;

    uint16_t spiTransfer(uint16_t value);
};