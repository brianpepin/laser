#pragma once

namespace Pins
{
    namespace Spi
    {
        constexpr static uint8_t Mosi   = 11;
        constexpr static uint8_t Miso   = 12;
        constexpr static uint8_t Sck    = 13;
        constexpr static uint8_t Ss     = 10;
    }

    namespace Gpio
    {
        constexpr static uint8_t Cs     = 2;        // PD2
        constexpr static uint8_t Irq    = PCINT23;  // PD7

        // GPIO expander port numbers
        namespace Inputs
        {
            constexpr static uint8_t EncoderA           = 0x01;
            constexpr static uint8_t EncoderB           = 0x02;
            constexpr static uint8_t EncoderSel         = 0x04;
            constexpr static uint8_t FireMom            = 0x08;
            constexpr static uint8_t FireLatch          = 0x10;
            constexpr static uint8_t InterlockEnable    = 0x20;
            constexpr static uint8_t OverTemp           = 0x40;
        }

        namespace Outputs
        {
            constexpr static uint8_t FireLed            = 0x80;
        }
    }

    namespace Tec
    {
        constexpr static uint8_t CsRead = 8;  // PB0
        constexpr static uint8_t CsSet  = 9;  // PB1
        constexpr static uint8_t Enable = A5; // PC5
    }

    namespace Laser
    {
        constexpr static uint8_t Cs     = A0; // PC0
        constexpr static uint8_t Reset  = A1; // PC1
    }

    namespace Power
    {
        constexpr static uint8_t Cs     = 4;  // PD4
    }

    namespace Led
    {
        constexpr static uint8_t Red    = 3; // PD3
        constexpr static uint8_t Green  = 5; // PD5
        constexpr static uint8_t Blue   = 6; // PD6
    }

    namespace Display
    {
        constexpr static uint8_t Cs     = A2; // PC2
        constexpr static uint8_t Dc     = A3; // PC3
        constexpr static uint8_t Reset  = A4; // PC4
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
