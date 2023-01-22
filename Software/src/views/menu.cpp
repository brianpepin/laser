#include "globals.h"
#include "fonts.h"
#include "macros.h"
#include "views/menu.h"

void MenuView::clearMenu()
{
    for (size_t idx = 0; idx < ARRAYSIZE(_items); idx++)
    {
        auto& item = _items[idx];
        item.text = nullptr;
        item.value = nullptr;
    }

    _title = nullptr;
    _sel = 0;
    _valueSelect = false;
    _fireChannel = Tec::Channel::Ktp; // disable firing
    _lastFireChannel = _fireChannel;
    _itemCount = 0;
    _buttonIndex = 0xff;
}

void MenuView::addItem(const __FlashStringHelper* text, Cmd cmd, Value* value)
{
    auto& item = _items[_itemCount];
    item.text = text;
    item.cmd = cmd;
    item.value = value;
    item.width = 0;

    _itemCount++;
    _update = true;
}

void MenuView::addButton(const __FlashStringHelper* text, Cmd cmd, uint8_t width)
{
    auto& item = _items[_itemCount];
    item.text = text;
    item.cmd = cmd;
    item.value = nullptr;
    item.width = width;

    if (_buttonIndex == 0xff)
    {
        _buttonIndex = _itemCount;
    }

    _itemCount++;
    _update = true;
}

void MenuView::mainMenu()
{
    clearMenu();

    size_t idx = 0;
    _values[idx].init(&settings.displayMode);
    addItem(F("DISPLAY MODE"), Cmd::ValueSelect, &_values[idx++]);
    addItem(F("CALIBRATION"), Cmd::Calibration);
    addItem(F("EXIT"), Cmd::Exit);
}

void MenuView::alignmentMenu()
{
    // laser firing will be hot here, so reset input state.
    input.reset();
    _fireChannel = Tec::Channel::Pump1;
    _lastFireChannel = _fireChannel;

    clearMenu();
    
    size_t idx = 0;
    _values[idx].init(ValueType::AlignCurrent, Tec::Channel::Pump1);
    addItem(F("PUMP 1 DRIVE CURRENT"), Cmd::ValueSelect, &_values[idx++]);
    _values[idx].init(ValueType::AlignCurrent, Tec::Channel::Pump2);
    addItem(F("PUMP 2 DRIVE CURRENT"), Cmd::ValueSelect, &_values[idx++]);
    _values[idx].init(&_fireChannel);
    addItem(F("PUMP SELECT"), Cmd::ValueSelect, &_values[idx++]);
    addButton(F("EXIT"), Cmd::Exit, 6);
}

void MenuView::calibrationMenu()
{
    clearMenu();
    addButton(F("PUMP 1"), Cmd::CalibratePump1, 10);
    addButton(F("PUMP 2"), Cmd::CalibratePump2, 10);
    addButton(F("VANADATE"), Cmd::CalibrateVanadate, 10);
    addButton(F("KTP"), Cmd::CalibrateKtp, 10);
    addButton(F("ALIGN"), Cmd::CalibrateAlign, 10);
    addButton(F("EXIT"), Cmd::Exit, 10);
}

void MenuView::calibrateItem(const __FlashStringHelper* title, Tec::Channel channel)
{
    // laser firing will be hot here, so reset input state.
    input.reset();

    size_t idx = 0;
    clearMenu();
    _title = title;
    _fireChannel = channel;
    _lastFireChannel = _fireChannel;

    if (channel == Tec::Channel::Pump1 || channel == Tec::Channel::Pump2)
    {
        _values[idx].init(ValueType::MaxCurrent, channel);
        addItem(F("MAX CURRENT"), Cmd::ValueSelect, &_values[idx]);
        idx++;
    }

    if (channel == Tec::Channel::Pump1 || channel == Tec::Channel::Pump2 || channel == Tec::Channel::Ktp)
    {
        _values[idx].init(ValueType::Current, channel);
        addItem(F("DRIVE CURRENT"), Cmd::ValueSelect, &_values[idx]);
        idx++;
    }

    _values[idx].init(ValueType::Temp, channel);
    addItem(F("TEMPERATURE"), Cmd::ValueSelect, &_values[idx]);
    idx++;

    addButton(F("SAVE"), Cmd::CalibrateSave, 4);
    addButton(F("CANCEL"), Cmd::CalibrateCancel, 6);
}

void MenuView::start(View* prevView)
{
    _prevView = prevView;
    laser.enable(false);
    mainMenu();
}

void MenuView::processCmd(Cmd cmd, View** newView)
{
    switch (cmd)
    {
        default:
        case Cmd::Exit:
            *newView = _prevView;
            break;

        case Cmd::Calibration:
            settings.save();
            calibrationMenu();
            break;

        case Cmd::CalibrateAlign:
            alignmentMenu();
            break;

        case Cmd::CalibratePump1:
            calibrateItem(F("PUMP 1"), Tec::Channel::Pump1);
            break;

        case Cmd::CalibratePump2:
            calibrateItem(F("PUMP 2"), Tec::Channel::Pump2);
            break;

        case Cmd::CalibrateVanadate:
            calibrateItem(F("VANADATE"), Tec::Channel::Vanadate);
            break;

        case Cmd::CalibrateKtp:
            calibrateItem(F("KTP"), Tec::Channel::Ktp);
            break;

        case Cmd::CalibrateCancel:
            settings.load();
            Management::restart();
            calibrationMenu();
            break;

        case Cmd::CalibrateSave:
            settings.save();
            Management::restart();
            calibrationMenu();
            break;

        case Cmd::ValueSelect:
            if (_items[_sel].value != nullptr)
            {
                _valueSelect = true;
                _update = true;
            }
            break;
    }
}

bool MenuView::tick(View** newView)
{
    if (_update)
    {
        _update = false;
        return true;
    }

    int8_t dir = input.getEncoderDirection();
    if (dir != 0)
    {
        if (_valueSelect)
        {
            _items[_sel].value->adjust(dir);
        }
        else
        {
            _sel += dir;

            if (_sel < 0)
            {
                _sel = 0;
            }
            else if (_sel >= _itemCount)
            {
                _sel = _itemCount - 1;
            }
        }

        return true;
    }

    if (input.getEncoderSelect())
    {
        if (_valueSelect)
        {
            _valueSelect = false;
            laser.enable(false);
        }
        else
        {
            processCmd(_items[_sel].cmd, newView);
        }
        return true;
    }

    if (input.getFireSwitch() != laser.getEnabled() || _fireChannel != _lastFireChannel)
    {
        _lastFireChannel = _fireChannel;
        switch(_fireChannel)
        {
            case Tec::Channel::Pump1:
                laser.enable(input.getFireSwitch(), Laser::Channel::Pump1);
                break;

            case Tec::Channel::Pump2:
                laser.enable(input.getFireSwitch(), Laser::Channel::Pump2);
                break;

            case Tec::Channel::Ktp:
                laser.enable(input.getFireSwitch());
                break;

            default:
                laser.enable(false);
        }
    }

    return false;
}

void MenuView::render()
{
    constexpr static uint8_t margin = 2;

    display.setFontDirection(0);
    u8g2_uint_t y = 0;

    if (_title != nullptr)
    {
        display.setFont(MENU_TITLE);
        y = display.getMaxCharHeight();
        display.setCursor(margin, y);
        display.print(_title);
        y += 2 * margin;
    }

    y += 2;
    display.setFont(MENU_FONT);

    u8g2_uint_t h = display.getMaxCharHeight() + (2 * margin);
    u8g2_uint_t w = display.getDisplayWidth() - 30;
    u8g2_uint_t x = 0;

    for (int8_t idx = 0; idx < _itemCount; idx++)
    {
        if (idx == _buttonIndex && idx != 0)
        {
            y += 2 * margin;
            x = w / 2;
        }

        if (_items[idx].width != 0)
        {
            w = _items[idx].width * display.getMaxCharWidth() + 2 * margin;
        }

        display.setCursor(x + margin, y + h - margin);
        display.print(_items[idx].text);

        if (_items[idx].value != nullptr)
        {
            display.setCursor(w / 2 + margin, y + h - margin);
            _items[idx].value->draw();
        }

        if (_sel == idx)
        {
            if (_valueSelect)
            {
                display.drawHLine(w / 2, y + h - 1, w / 2);
            }
            else
            {
                display.drawFrame(x, y, w, h);
            }
        }

        if (idx >= _buttonIndex && (_buttonIndex != 0 || (idx % 2) == 0))
        {
            x += w;
            x += 3 * display.getMaxCharWidth();
        }
        else
        {
            y += h;
            x = 0;
        }
    }
}

void MenuView::Value::init(ValueType type, Tec::Channel channel)
{
    _type = type;
    _channel = channel;
    _fireChannel = nullptr;
    _displayMode = nullptr;
    _value = 0;
}

void MenuView::Value::init(Tec::Channel* fireChannel)
{
    _type = ValueType::Current;
    _channel = Tec::Channel::Pump1;;
    _fireChannel = fireChannel;
    _displayMode = nullptr;
    _value = 0;
    updateState();
}

void MenuView::Value::init(DisplayMode* displayMode)
{
    _type = ValueType::Current;
    _channel = Tec::Channel::Pump1;;
    _fireChannel = nullptr;
    _displayMode = displayMode;
    _value = 0;
}

void MenuView::Value::draw()
{
    if (_fireChannel)
    {
        const __FlashStringHelper* s;
        switch (*_fireChannel)
        {
            case Tec::Channel::Pump1: s = F("PUMP 1"); break;
            case Tec::Channel::Pump2: s = F("PUMP 2"); break;
            case Tec::Channel::Ktp: s = F("BOTH"); break;
            default: break;
        }
        display.print(s);
    }
    else if (_displayMode)
    {
        const __FlashStringHelper* s;
        switch (*_displayMode)
        {
            case DisplayMode::Current: s = F("DRIVE CURRENT"); break;
            case DisplayMode::Power:   s = F("OUTPUT POWER"); break;
            default: break;
        }
        display.print(s);
    }
    else
    {
        float value = get();
        display.print(value, 1);
        display.print(_type == ValueType::Temp ? 'C' : 'A');
    }
}

void MenuView::Value::adjust(int8_t dir)
{
    if (_fireChannel)
    {
        _value += dir;
        if (_value > 2) _value = 2;
        else if (_value < 0) _value = 0;
        updateState();
    }
    else if (_displayMode)
    {
        _value += dir;
        if (_value > 1) _value = 1;
        else if (_value < 0) _value = 0;
        updateState();
    }
    else if (_channel == Tec::Channel::Ktp && _type == ValueType::Temp)
    {
        // KTP temp needs finer control of temperature
        float value = get();
        float adj = dir;
        adj /= 10.0;
        value += adj;
        set(value);
    }
    else
    {
        float value = get();
        float adj = dir;
        adj /= 2.0;
        value += adj;
        set(value);
    }
}

void MenuView::Value::updateState()
{
    if (_fireChannel)
    {
        switch (_value)
        {
            case 0: *_fireChannel = Tec::Channel::Pump1; break;
            case 1: *_fireChannel = Tec::Channel::Pump2; break;
            case 2: *_fireChannel = Tec::Channel::Ktp; break;
        }
    }
    else if (_displayMode)
    {
        *_displayMode = (DisplayMode)(int)_value;
    }
}

float MenuView::Value::get()
{
    switch (_channel)
    {
        case Tec::Channel::Pump1:
            switch (_type)
            {
                case ValueType::MaxCurrent:
                    return settings.limits.maxPump1Current;
                case ValueType::Current:
                case ValueType::AlignCurrent:
                    return laser.getCurrent(Laser::Channel::Pump1);
                case ValueType::Temp:
                    return settings.temps.pump1;
            }
            break;

        case Tec::Channel::Pump2:
            switch (_type)
            {
                case ValueType::MaxCurrent:
                    return settings.limits.maxPump2Current;
                case ValueType::Current:
                case ValueType::AlignCurrent:
                    return laser.getCurrent(Laser::Channel::Pump2);
                case ValueType::Temp:
                    return settings.temps.pump2;
            }
            break;

        case Tec::Channel::Vanadate:
            return settings.temps.vanadate;

        case Tec::Channel::Ktp:
            switch (_type)
            {
                default:
                    break;
                case ValueType::Current:
                    return laser.getCurrent();
                case ValueType::Temp:
                    return settings.temps.ktp;
            }
            break;
    }

    return 0;
}

void MenuView::Value::set(float value)
{
    if (_type == ValueType::Temp)
    {
        value = max(value, 0);
        value = min(value, 100);
    }
    else if (_type == ValueType::MaxCurrent)
    {
        value = max(value, 0);
        value = min(value, laser.getDriverMaxCurrent());
    }

    switch (_channel)
    {
        case Tec::Channel::Pump1:
            switch (_type)
            {
                case ValueType::MaxCurrent:
                    settings.limits.maxPump1Current = value;
                    laser.setCurrent(min(
                        laser.getCurrent(Laser::Channel::Pump1),
                        settings.limits.maxPump1Current),
                        Laser::Channel::Pump1);
                    break;
                case ValueType::Current:
                    laser.setCurrent(value, Laser::Channel::Pump1);
                    laser.setCurrent(0, Laser::Channel::Pump2);
                    break;
                case ValueType::AlignCurrent:
                    laser.setCurrent(value, Laser::Channel::Pump1);
                    break;
                case ValueType::Temp:
                    tec.setTemp(_channel, value);
                    settings.temps.pump1 = value;
                    break;
            }
            break;

        case Tec::Channel::Pump2:
            switch (_type)
            {
                case ValueType::MaxCurrent:
                    settings.limits.maxPump2Current = value;
                    laser.setCurrent(min(
                        laser.getCurrent(Laser::Channel::Pump2),
                        settings.limits.maxPump2Current),
                        Laser::Channel::Pump2);
                    break;
                case ValueType::Current:
                    laser.setCurrent(value, Laser::Channel::Pump2);
                    laser.setCurrent(0, Laser::Channel::Pump1);
                    break;
                case ValueType::AlignCurrent:
                    laser.setCurrent(value, Laser::Channel::Pump2);
                    break;
                case ValueType::Temp:
                    tec.setTemp(_channel, value);
                    settings.temps.pump2 = value;
                    break;
            }
            break;

        case Tec::Channel::Vanadate:
            tec.setTemp(_channel, value);
            settings.temps.vanadate = value;
            break;

        case Tec::Channel::Ktp:
            switch (_type)
            {
                default:
                    break;
                case ValueType::Current:
                    laser.setCurrent(value);
                    break;
                case ValueType::Temp:
                    tec.setTemp(_channel, value);
                    settings.temps.ktp = value;
                    break;
            }
            break;
    }
}
