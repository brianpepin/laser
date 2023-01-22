#include <Arduino.h>
#include <EEPROM.h>
#include "settings.h"
#include "config.h"

#define VERSION 1

void Settings::load()
{
    uint8_t ver = EEPROM.read(0);

    if (ver == VERSION)
    {
        EEPROM.get(1, *this);
    }
    else
    {
        limits.maxPump1Current = ::Limits::Current::Pump1;
        limits.maxPump2Current = ::Limits::Current::Pump2;

        temps.pump1 = ::Defaults::Temperatures::Pump1;
        temps.pump2 = ::Defaults::Temperatures::Pump2;
        temps.vanadate = ::Defaults::Temperatures::Vanadate;
        temps.ktp = ::Defaults::Temperatures::Ktp;

        current = 0;
        displayMode = DisplayMode::Current;
    }
}

void Settings::save()
{
    EEPROM.update(0, VERSION);
    EEPROM.put(1, *this);
}
