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

    class DiagnosticCommands : public Parser
    {
    public:
        bool parse(const char* cmd) override;
        void usage() override;
    };

    namespace Cmds
    {
        static GlobalCommands global;
        static DiagnosticCommands diag;
    }

    constexpr size_t _bufferMax = 10;
    char _buffer[_bufferMax + 1];
    uint8_t _bufferLen;
    static Parser* _parser = &Cmds::global;
    SystemStatus _simulatedStatus{};
    
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
        Serial.print(status.power.laserOutputPower);
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
        Serial.print(status.power.batteryVoltage);
        Serial.print('V');
        if (status.power.batteryCharging) Serial.print(F(" [Charging]"));
        Serial.println();
    }

    void printAdcLine(const __FlashStringHelper* text, int16_t value, float fvalue)
    {
        size_t len;
        len = Serial.print(text);
        for (size_t ch = 0; ch < 18 - len; ch++) Serial.print(' ');
        len = Serial.print(fvalue);
        for (size_t ch = 0; ch < 10 - len; ch++) Serial.print(' ');
        Serial.print(F("("));
        Serial.print(value);
        Serial.println(F(")"));
    }

    void printAdc()
    {
        auto& status = Management::getSystemStatus();
        uint16_t value;
        float fvalue;

        Serial.println();

        value = status.power.adc.batteryCharging;
        bool charge = status.power.batteryCharging;
        printAdcLine(F("Battery Charging: "), value, charge ? 1.0 : 0.0);

        value = status.power.adc.batteryVoltage;
        fvalue = status.power.batteryVoltage;
        printAdcLine(F("Battery Voltage: "), value, fvalue);

        value = status.power.adc.batteryCurrent;
        fvalue = status.power.batteryCurrent;
        printAdcLine(F("Battery Current: "), value, fvalue);

        value = status.power.adc.laserOutputPower;
        fvalue = status.power.laserOutputPower;
        printAdcLine(F("Laser Output: "), value, fvalue);

        Serial.println();
    }

    void initializeSimulation()
    {
        _simulatedStatus.laser.ok = true;

        _simulatedStatus.power.batteryCharging = false;
        _simulatedStatus.power.batteryCurrent = 0;
        _simulatedStatus.power.batteryVoltage = 8.4;
        _simulatedStatus.power.laserOutputPower = 0;

        _simulatedStatus.power.adc.laserOutputPower = 512;

        _simulatedStatus.tec.ktp.temp = Defaults::Temperatures::Ktp;
        _simulatedStatus.tec.pump1.temp = Defaults::Temperatures::Pump1;
        _simulatedStatus.tec.pump2.temp = Defaults::Temperatures::Pump2;
        _simulatedStatus.tec.vanadate.temp = Defaults::Temperatures::Vanadate;
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

            case 'd':
                _parser = &Cmds::diag;
                return true;
        }

        return false;
    }

    void GlobalCommands::usage()
    {
        Serial.println(F("\ns : Status Report"));
        Serial.println(F("a : Read ADC values"));
        Serial.println(F("f : Toggle fire switch"));
        Serial.println(F("d : Enter diagnostic menu\n"));
    }

    bool DiagnosticCommands::parse(const char* cmd)
    {
        switch (*cmd)
        {
            case 's':
                initializeSimulation();
                Management::setSimulation(&_simulatedStatus);
                return true;

            case 'e':
                Management::setSimulation(nullptr);
                return true;

            case 'r':
                Management::restart();
                return true;

            case 'x':
                _parser = &Cmds::global;
                return true;
        }

        return false;
    }

    void DiagnosticCommands::usage()
    {
        Serial.println(F("\ns : Enter simulation mode"));
        Serial.println(F("e : End simulation mode"));
        Serial.println(F("r : Reset"));
        Serial.println(F("x : Exit menu\n"));
    }

    void parse(const char* cmd)
    {
        if (*cmd == '\0')
        {
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