#include "globals.h"
#include "fonts.h"
#include "views/running.h"

void RunningView::start(View*)
{
    Management::enable(true);
    input.reset();
    laser.enable(false);
    laser.setCurrent(settings.current);
}

void RunningView::stop()
{
    input.reset();
    laser.enable(false);
}

bool RunningView::tick(View** newView)
{
    bool update = false;

    auto& status = Management::getSystemStatus();

    uint32_t m = millis();
    if (m - _millis > 250)
    {
        _millis = m;
        _pump1Current = status.laser.led1.current;
        _pump2Current = status.laser.led2.current;
        _outputPower = status.outputPower;    
        _tecStatus = status.tec;
        _laserOk = status.laser.ok;

        float ledPower =
            (status.laser.led1.voltage * status.laser.led1.current +
             status.laser.led2.voltage * status.laser.led2.current);

        _efficiency = ledPower != 0 ? _outputPower * 100 / ledPower : 0.0;

        update = true;
    }

    if (status.ok)
    {
        if (!_ok)
        {
            laser.enable(false);
            input.reset();
            _ok = true;
        }

        if (laser.getEnabled() != input.getFireSwitch())
        {
            laser.enable(input.getFireSwitch());
        }
    }
    else if (_ok)
    {
        laser.enable(false);
        input.reset();
        _ok = false;
    }

    float dir = input.getEncoderDirection();

    if (dir != 0)
    {
        float cur = laser.getCurrent();
        cur += (dir / 2);
        laser.setCurrent(cur);
        settings.current = laser.getCurrent();
        settings.save();
        update = true;
    }

    if (input.getEncoderSelect())
    {
        *newView = Management::getView(ViewId::Menu);
    }

    return update;
}

static void floatToStr(float value, char suffix, char* text)
{
    int v = (int)value;
    itoa(v, text, 10);
    value -= v;
    v = (int)(abs(value * 10));
    size_t ch = strlen(text);
    text[ch++] = '.';
    text[ch++] = (char)(0x30 + v);
    text[ch++] = suffix;
    text[ch] = '\0';
}

static void renderItem(u8g2_uint_t x, u8g2_uint_t y, const char* text, bool ok)
{
    display.setDrawColor(ok ? 1 : 0);
    u8g2_uint_t len = display.drawStr(x, y, text);
    display.setDrawColor(1);

    if (!ok)
    {
        int8_t h = display.getMaxCharHeight();
        display.drawFrame(x - 1, y - h, len + 2, h + 2);
    }
}

static u8g2_uint_t renderRow(u8g2_uint_t x, u8g2_uint_t y, int8_t h, const char* text, const float* current, bool currentOk, const Tec::ChannelStatus& temp)
{
    char buffer[20];

    renderItem(x, y, text, true);

    x += 50;

    if (current != nullptr)
    {
        floatToStr(*current, 'A', buffer);
        renderItem(x, y, buffer, currentOk);
    }

    x += 40;
    floatToStr(temp.temp, 'C', buffer);
    renderItem(x, y, buffer, temp.ok);

    return y + h + 2;
}

const char* renderPower(float power)
{
    if (power < 1)
    {
        display.print(power * 1000.0, 1);
        return "mW";
    }
    else
    {
        display.print(power, 1);
        return "W";
    }
}

void RunningView::render()
{
    display.setFont(PRIMARY_VALUE_FONT);
    display.setFontDirection(0);
    int8_t h = display.getMaxCharHeight();
    u8g2_uint_t y = h;    
    display.setCursor(0, y);

    const char* units;

    switch (settings.displayMode)
    {
        default:
        case DisplayMode::Current:
            display.print(laser.getCurrent(), 1);
            display.setFont(PRIMARY_UNITS_FONT);
            display.print('A');
            display.setFont(SECONDARY_VALUE_FONT);
            h = display.getMaxCharHeight();
            y += (15 * h) / 10;
            display.setCursor(0, y);
            display.print("Output: ");
            units = renderPower(_outputPower);
            display.print(units);
            break;
        
        case DisplayMode::Power:
            units = renderPower(_outputPower);
            display.setFont(PRIMARY_UNITS_FONT);
            display.print(units);
            display.setFont(SECONDARY_VALUE_FONT);
            h = display.getMaxCharHeight();
            y += (15 * h) / 10;
            display.setCursor(0, y);
            display.print("Current: ");
            display.print(laser.getCurrent(), 1);
            display.print('A');
            break;
    }

    display.setFont(DETAIL_FONT);
    u8g2_uint_t x = display.getWidth() - display.getMaxCharWidth() * 25;

    h = display.getMaxCharHeight();

    y = h + 15;
    y = renderRow(x, y, h, "PUMP 1", &_pump1Current, _laserOk, _tecStatus.pump1);
    y = renderRow(x, y, h, "PUMP 2", &_pump2Current, _laserOk, _tecStatus.pump2);
    y = renderRow(x, y, h, "VANADATE", nullptr, true, _tecStatus.vanadate);
    y = renderRow(x, y, h, "KTP", nullptr, true, _tecStatus.ktp);
    display.setCursor(x, y);
    display.print("EFFICIENCY");
    display.setCursor(x + 90, y);
    display.print(_efficiency, 1);
    display.print('%');
}