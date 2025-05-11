#pragma once
#include "view.h"

class MenuView : public View
{
public:
    void start(View* prevView) override;
    void stop() override {};
    bool tick(View** newView) override;
    void render() override;

private:

    enum class Cmd
    {
        Exit,
        Calibration,
        CalibratePump1,
        CalibratePump2,
        CalibrateVanadate,
        CalibrateKtp,
        CalibrateAlign,
        CalibrateAdc,
        ValueSelect,
        CalibrateSave,
        CalibrateCancel,
        CalibrateAlignExit,
    };

    enum class ValueType
    {
        MaxCurrent,
        AlignCurrent,
        Current,
        Temp,
        Power,
        Adc
    };

    class Value
    {
    public:
        void init(ValueType type, Tec::Channel channel);
        void init(Tec::Channel* fireChannel);
        void init(DisplayMode* displayMode);
        void init(ValueType type, Settings::Calibration::Point* calibrationPoint, Settings::Calibration::Point* setPoint);
        void adjust(int8_t dir, uint8_t velocity);
        void draw();
        bool tick();
        bool readOnly() { return _type == ValueType::Adc; }
    private:
        ValueType _type;
        Tec::Channel _channel;
        Tec::Channel* _fireChannel;
        DisplayMode* _displayMode;
        Settings::Calibration::Point* _calibrationPoint;
        Settings::Calibration::Point* _setPoint;
        int8_t _value;
        float get();
        void set(float value);
        void updateState();
    };

    constexpr static size_t c_maxItemValues = 3;

    struct Item
    {
        const __FlashStringHelper* text;
        Value* values[c_maxItemValues];
        Cmd cmd;
        uint8_t width;
    };

    View* _prevView;
    const __FlashStringHelper* _title;
    Value _values[6];
    Item _items[12];
    Settings::Calibration::Point _setPoints[3];
    bool _update;
    uint8_t _valueSelect;
    Tec::Channel _fireChannel;
    Tec::Channel _lastFireChannel;
    int8_t _sel;
    uint8_t _itemCount;
    uint8_t _buttonIndex;

    void clearMenu();
    void addItem(const __FlashStringHelper* text, Cmd cmd, Value* value1 = nullptr, Value* value2 = nullptr, Value* value3 = nullptr);
    void addButton(const __FlashStringHelper* text, Cmd cmd, uint8_t width);
    void mainMenu();
    void alignmentMenu();
    void calibrationMenu();
    void adcMenu();
    void calibrateItem(const __FlashStringHelper* title, Tec::Channel channel);
    void processCmd(Cmd cmd, View** newView);
};