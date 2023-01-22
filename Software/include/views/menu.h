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
        ValueSelect,
        CalibrateSave,
        CalibrateCancel
    };

    enum class ValueType
    {
        MaxCurrent,
        AlignCurrent,
        Current,
        Temp
    };

    class Value
    {
    public:
        void init(ValueType type, Tec::Channel channel);
        void init(Tec::Channel* fireChannel);
        void init(DisplayMode* displayMode);
        void adjust(int8_t dir);
        void draw();
    private:
        ValueType _type;
        Tec::Channel _channel;
        Tec::Channel* _fireChannel;
        DisplayMode* _displayMode;
        int8_t _value;
        float get();
        void set(float value);
        void updateState();
    };

    struct Item
    {
        const __FlashStringHelper* text;
        Value* value;
        Cmd cmd;
        uint8_t width;
    };

    View* _prevView;
    const __FlashStringHelper* _title;
    Value _values[3];
    Item _items[6];
    bool _update;
    bool _valueSelect;
    Tec::Channel _fireChannel;
    Tec::Channel _lastFireChannel;
    int8_t _sel;
    uint8_t _itemCount;
    uint8_t _buttonIndex;

    void clearMenu();
    void addItem(const __FlashStringHelper* text, Cmd cmd, Value* value = nullptr);
    void addButton(const __FlashStringHelper* text, Cmd cmd, uint8_t width);
    void mainMenu();
    void alignmentMenu();
    void calibrationMenu();
    void calibrateItem(const __FlashStringHelper* title, Tec::Channel channel);
    void processCmd(Cmd cmd, View** newView);
};