#include "globals.h"
#include "config.h"
#include "fonts.h"
#include "views/battery.h"

BatteryView::BatteryView()
{
    _state.draw = false;
    _state.blink = false;
    _state.level = 0x0f;
}

void BatteryView::start(View*)
{
    Management::enable(false);
    _state.level = 0x0f;
}

bool BatteryView::tick(View**)
{
    bool update = false;

    constexpr static uint16_t maxLevels = 5;

    auto& status = Management::getSystemStatus();

    float level = status.battery.voltage;
    float range = Limits::Voltage::HiBat - Limits::Voltage::LowBat;

    level -= Limits::Voltage::LowBat;
    if (level < 0) level = 0;

    uint32_t newLevel = (int)((level * (maxLevels + 1)) / range);

    if (newLevel > maxLevels)
    {
        newLevel = maxLevels;
    }

    if (newLevel != _state.level)
    {
        _state.level = newLevel;
        _state.draw = true;
        _state.blink = false;
        update = true;
    }

    if (_state.charging != status.battery.charging)
    {
        _state.charging = status.battery.charging;
        _state.blink = false;
        update = true;
    }

    uint32_t m = millis();
    if (m - _ticks > 500)
    {
        _ticks = m;

        if (_state.level == 0)
        {
            _state.draw = !_state.draw;
            update = true;
        }
        else if (_state.charging)
        {
            _state.blink = !_state.blink;
            update = true;
        }
    }

    return update;
}

void BatteryView::render()
{
    render(true);
}

void BatteryView::renderOverlay()
{
    render(false);
}

void BatteryView::render(bool centered)
{
    if (_state.draw && (!centered || _state.charging || input.getInterlockSwitch()))
    {
        display.setFont(BATTERY_FONT);

        if (centered)
        {
            display.setFontDirection(0);
            display.setCursor(120, 42);
        }
        else
        {
            display.setFontDirection(1);
            display.setCursor(255 - display.getMaxCharHeight(), 0);
        }

        uint8_t level = _state.level;
        if (_state.blink)
        {
            level--;
        }

        display.print((char)(0x30 + level));
    }
}