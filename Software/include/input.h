#pragma once

#include <XRA1402.h>

//
// Input works as follows:  Inputs that are momentary in
// nature will return a value when the input changes. Inputs
// like the fire or interlock switches return their correct
// state.
//

class Input
{
public:
    Input();

    int8_t getEncoderDirection();
    bool getEncoderSelect();
    bool getFireSwitch();
    bool getInterlockSwitch();
    bool getOverTemp();

    void toggleFireSwitch();

    void setFireSwitchLed(bool on);

    void reset();
    void processInterrupt();

private:
    XRA1402 _gpio;

    struct State
    {
        uint8_t Select      : 1;
        uint8_t Interlock   : 1;
        uint8_t Fire        : 1;
        uint8_t Temp        : 1;
    };

    struct EncoderData
    {
        uint8_t pending : 1;
        uint8_t ccw : 1;
        uint8_t unused : 6;
        uint32_t timestamp;
    };
    
    volatile State _state;
    volatile int8_t _encoderDir;
    volatile EncoderData _encoderData;
};