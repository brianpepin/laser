#pragma once
#include "view.h"

//
// BatteryView - displays battery status.
//
class BatteryView : public View
{
public:
    BatteryView();
    void start(View* ) override;
    void stop() override {};
    bool tick(View** newView) override;
    void render() override;
    void renderOverlay();

private:

    struct State
    {
        uint8_t level    : 5;
        uint8_t draw     : 1;
        uint8_t blink    : 1;
        uint8_t charging : 1;
    } _state;

    uint32_t _ticks = 0;

    void render(bool centered);
};
