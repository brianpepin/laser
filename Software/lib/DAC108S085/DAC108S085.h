
#pragma once

//
// DAC108S085 8 Channel Digital to Analog Converter
//
// Datasheet: https://www.ti.com/lit/ds/symlink/dac108s085.pdf?HQS=dis-mous-null-mousermode-dsf-pf-null-wwe&ts=1631993078088
//

class DAC108S085
{
public:

    DAC108S085(uint8_t csPin);

    // Channel 0 = 7, value is 10 bits.
    void writeValue(uint8_t channel, uint16_t value);

    constexpr static uint16_t max = 1024;

private:
    uint8_t _cs;

    uint16_t spiTransfer(uint16_t value);
};