#include "globals.h"
#include "macros.h"
#include "console.h"

// todo diag
#include "ADC104S021.h"
#include "config.h"
#include "power.h"

namespace Console
{
    class Parser
    {
    public:
        virtual bool singleChar() { return true; }
        virtual bool parse(const char* cmd) = 0;
        virtual void usage() = 0;
    };

    class GlobalCommands : public Parser
    {
    public:
        bool parse(const char* cmd) override;
        void usage() override;
    };

    namespace Cmds
    {
        static GlobalCommands global;
    }

    constexpr size_t _bufferMax = 10;
    char _buffer[_bufferMax + 1];
    uint8_t _bufferLen;
    static Parser* _parser = &Cmds::global;
    
    void printTecChannelStatus(const Tec::ChannelStatus& tecStatus)
    {
        Serial.print(tecStatus.temp);
        Serial.print('C');
        if (tecStatus.ok) Serial.print(F(" [Ok]"));
        Serial.println();
    }

    void printPumpStatus(const MAX20096::LEDStatus& status, const Tec::ChannelStatus& tecStatus)
    {
        Serial.print(F("Enabled      : "));
        Serial.println(status.enabled);

        Serial.print(F("Set Current  : "));
        Serial.print(status.setCurrent);
        Serial.println('A');

        Serial.print(F("Set PWM      : "));
        Serial.print(status.setPwm * 100.0);
        Serial.println('%');

        Serial.print(F("Current      : "));
        Serial.print(status.current);
        Serial.println('A');

        Serial.print(F("Voltage      : "));
        Serial.print(status.voltage);
        Serial.println('V');

        Serial.print(F("Flags        :"));
        if (status.exception) Serial.print(F(" [exception]"));
        if (status.overVoltage) Serial.print(F(" [OV]"));
        if (status.overCurrent) Serial.print(F(" [OC]"));
        if (status.shortDetected) Serial.print(F(" [short]"));
        if (status.openDetected) Serial.print(F(" [open]"));
        Serial.println();
        Serial.print(F("Temp         : "));
        printTecChannelStatus(tecStatus);
    }

    void printStatus()
    {
        auto& status = Management::getSystemStatus();

        Serial.println();

        if (status.ok)
        {
            Serial.println(F("System OK\n"));
        }

        Serial.print(F("Laser"));
        if (status.laser.ok) Serial.print(F(" [Ok]"));
        Serial.println();
        Serial.println(F("-----"));
        Serial.print(F("Output Power : "));
        Serial.print(status.outputPower);
        Serial.println('W');
        Serial.print(F("Die Temp     : "));
        Serial.print(status.laser.dieTemp);
        Serial.print('C');
        if (status.laser.thermalWarning) Serial.print(" [Warn]");
        if (status.laser.thermalShutdown) Serial.print(" [Shutdown]");
        if (status.laser.overtemp) Serial.print(" [Mosfet Temp]");
        Serial.println();

        Serial.print(F("Nd:YVO4 Temp : "));
        printTecChannelStatus(status.tec.vanadate);

        Serial.print(F("KTP Temp     : "));
        printTecChannelStatus(status.tec.ktp);

        Serial.println();
        Serial.println(F("Pump 1"));
        Serial.println(F("------"));
        printPumpStatus(status.laser.led1, status.tec.pump1);

        Serial.println();
        Serial.println(F("Pump 2"));
        Serial.println(F("------"));
        printPumpStatus(status.laser.led2, status.tec.pump2);

        Serial.println();
        Serial.println(F("Battery"));
        Serial.println(F("-------"));
        Serial.print(F("Voltage      : "));
        Serial.print(status.battery.voltage);
        Serial.print('V');
        if (status.battery.charging) Serial.print(F(" [Charging]"));
        Serial.println();
    }

    void printAdcLine(const __FlashStringHelper* text, int16_t value, float fvalue)
    {
        Serial.print(text);
        Serial.print(fvalue);
        Serial.print(F(" ("));
        Serial.print(value);
        Serial.println(F(")"));
    }

    void printAdc()
    {
        ADC104S021 adc(Pins::Power::Cs);
        Power power;
        int16_t value;
        float fvalue;

        Serial.println();

        value = adc.readValue(0);
        bool charge = power.isBatteryCharging();
        printAdcLine(F("Battery Charging: "), value, charge ? 1.0 : 0.0);

        value = adc.readValue(1);
        fvalue = power.getBatteryVoltage();
        printAdcLine(F("Battery Voltage: "), value, fvalue);

        value = adc.readValue(2);
        fvalue = power.getBatteryCurrent();
        printAdcLine(F("Battery Current: "), value, fvalue);

        value = adc.readValue(3);
        fvalue = power.getLaserOutputPower();
        printAdcLine(F("Laser Output: "), value, fvalue);

        Serial.println();
    }

    bool GlobalCommands::parse(const char* cmd)
    {
        switch (*cmd)
        {
            case 's':
                printStatus();
                return true;

            case 'a':
                printAdc();
                return true;

            case 'f':
                input.toggleFireSwitch();
                return true;
        }

        return false;
    }

    void GlobalCommands::usage()
    {
        Serial.println(F("\ns : Status"));
        Serial.println(F("a : Read ADC values"));
        Serial.println(F("f : Toggle fire switch\n"));
    }

    void parse(const char* cmd)
    {
        if (*cmd == '\0')
        {
            _parser = &Cmds::global;
            _parser->usage();
            return;
        }

        if (_parser->singleChar())
        {
            while (*cmd)
            {
                if (!_parser->parse(cmd))
                {
                    _parser->usage();
                    return;
                }
                cmd++;
            }
        }
        else
        {
            _parser->parse(cmd);
        }

        _parser->usage();
    }

    void tick()
    {
        while (Serial.available())
        {
            char ch = (char)Serial.read();

            switch (ch)
            {
                case '\e':
                    _bufferLen = 0;
                    Serial.println();
                    _parser = &Cmds::global;
                    _parser->usage();
                    break;

                case '\n':
                case '\r':
                    _buffer[_bufferLen] = '\0';
                    Serial.println();
                    parse(_buffer);
                    _bufferLen = 0;
                    break;

                case '\b':
                    if (_bufferLen > 0)
                    {
                        _bufferLen--;
                        Serial.print(F("\b \b"));
                    }

                default:
                    if (_bufferLen < _bufferMax &&
                        ((ch >= 'a' && ch <= 'z') ||
                         (ch >= '0' && ch <= '9') ||
                         ch == '.'))
                    {
                        _buffer[_bufferLen++] = ch;
                        Serial.print(ch);
                    }
                    break;
            }
        }
    }
}