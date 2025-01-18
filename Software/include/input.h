#pragma once

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

    void reset();
    void processInterrupt();

private:

    struct State
    {
        uint8_t Select      : 1;
        uint8_t Interlock   : 1;
        uint8_t Fire        : 1;
        uint8_t Temp        : 1;
    };
    
    volatile State _state;
    volatile int8_t _encoderDir;
};