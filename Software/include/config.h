#pragma once

namespace Pins
{
    namespace Spi
    {
        constexpr static uint8_t Mosi   = PIN_SPI_MOSI;
        constexpr static uint8_t Miso   = PIN_SPI_MISO;
        constexpr static uint8_t Sck    = PIN_SPI_SCK;
        constexpr static uint8_t Ss     = PIN_SPI_SS;
    }

    namespace Inputs
    {
        // All inputs are interrupt driven and must be on the
        // same port.
        constexpr static uint8_t EncoderA           = PIN3;
        constexpr static uint8_t EncoderB           = PIN2;
        constexpr static uint8_t EncoderSel         = PIN0;
        constexpr static uint8_t Fire               = PIN1;
        constexpr static uint8_t InterlockEnable    = PIN4;
        constexpr static uint8_t OverTemp           = PIN5;
        static PORT_t&           Port               = PORTD;

        // Hardware hacks -- PC board has these pins assigned wrong
        constexpr static uint8_t InterlockEnableHH  = PIN_PB7;
        constexpr static uint8_t OverTempHH         = PIN_PB2;
    }

    namespace Tec
    {
        constexpr static uint8_t CsRead = PIN_PB4;
        constexpr static uint8_t CsSet  = PIN_PB3;
        constexpr static uint8_t Enable = PIN_PB5;
    }

    namespace Laser
    {
        constexpr static uint8_t Cs     = PIN_PB0;
        constexpr static uint8_t Reset  = PIN_PB1;
    }

    namespace Power
    {
        constexpr static uint8_t Cs     = PIN_PB6;
    }

    namespace Led
    {
        constexpr static uint8_t Red    = PIN_PC2;
        constexpr static uint8_t Green  = PIN_PC1;
        constexpr static uint8_t Blue   = PIN_PC0;

        constexpr static uint8_t Fire   = PIN_PC3;
        constexpr static uint8_t Ready  = PIN_PC4;
    }

    namespace Display
    {
        constexpr static uint8_t Cs     = PIN_PE0;
        constexpr static uint8_t Dc     = PIN_PE2;
        constexpr static uint8_t Reset  = PIN_PE1;
    }
}

namespace Limits
{
    namespace Current
    {
        constexpr static float Pump1 = 25;
        constexpr static float Pump2 = 25;
    }

    namespace Voltage
    {
        constexpr static float HiBat = 8.4;
        constexpr static float LowBat = 7.5;
        constexpr static float CriticalBat = 7.0;
    }

    namespace Temperature
    {
        constexpr static float DisconnectLimit = -30;
    }
}

namespace Tolerances
{
    namespace Temperature
    {
        constexpr static float Pump = 3.0;
        constexpr static float Vanadate = 5.0;
        constexpr static float Ktp = 1.5;
    }
}

namespace Defaults
{
    namespace Temperatures
    {
        constexpr static float Pump1 = 27.5;
        constexpr static float Pump2 = 23.5;
        constexpr static float Vanadate = 23;
        constexpr static float Ktp = 29.6;
    }

    namespace Currents
    {
        namespace Tec
        {
            constexpr static float Pump     = 1.0; // 8.4 amps
            constexpr static float Vanadate = .85; // 6 amps
            constexpr static float Ktp      = .75; // 5.5 amps
        }
    }
}

namespace Calibration
{
    namespace LaserMonitor
    {
        constexpr static float Slope = .00562979359477001;
        constexpr static float Offset = 0;
    }

    namespace Battery
    {
        namespace Voltage
        {
            constexpr static float Slope = 0.008974358974358974358974358974359;
            constexpr static float Offset = 0.44871794871794871794871794871795;
        }

        namespace Current
        {
            constexpr static float Slope = 1;
            constexpr static float Offset = 0;
        }
    }

    // Current slew when ramping up the pump current
    namespace Slew
    {
        constexpr static float Step = .5;
        constexpr static uint8_t Delay = 10;
    }
}
