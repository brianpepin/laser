
#pragma once

//
// ADC104S021 4 Channel Analog to Digital Converter
//
// Datasheet: https://www.ti.com/lit/ds/symlink/adc104s021.pdf?HQS=dis-mous-null-mousermode-dsf-pf-null-wwe&ts=1631992329711
//

class ADC104S021
{
public:

    ADC104S021(uint8_t csPin);

    // Channel 0 = 3, value is 10 bits.
    uint16_t readValue(uint8_t channel);

    constexpr static uint16_t max = 1024;

private:
    uint8_t _cs;
};