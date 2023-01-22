#pragma once
#include "view.h"

class RunningView : public View
{
public:
    void start(View* ) override;
    void stop() override;
    bool tick(View** newView) override;
    void render() override;

private:
    uint32_t _millis = 0;
    bool _ok = false;
    bool _laserOk = false;
    float _outputPower = -1;
    float _pump1Current = -1;
    float _pump2Current = -1;
    float _efficiency = -1;
    Tec::Status _tecStatus;
};
