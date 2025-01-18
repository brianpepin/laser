
#include "globals.h"
#include "config.h"

#define PIN_HIGH(state, pin) ((state & (1 << pin)) != 0)

Input::Input()
{
}

int8_t Input::getEncoderDirection()
{
    cli();
    int8_t dir = _encoderDir;
    _encoderDir = 0;
    sei();
    return dir;
}

bool Input::getEncoderSelect()
{
    bool sel = _state.Select;
    _state.Select = false;
    return sel;
}

bool Input::getFireSwitch()
{
    return _state.Fire;
}

bool Input::getInterlockSwitch()
{
    //return _state.Interlock;
    return digitalRead(Pins::Inputs::InterlockEnableHH);
}

bool Input::getOverTemp()
{
    //return _state.Temp;
    return digitalRead(Pins::Inputs::OverTempHH);
}

void Input::toggleFireSwitch()
{
    _state.Fire = !_state.Fire;
}

void Input::reset()
{
    // Input direction for all input pins
    constexpr static uint8_t inputs =
        1 << Pins::Inputs::EncoderA |
        1 << Pins::Inputs::EncoderB |
        1 << Pins::Inputs::EncoderSel |
        1 << Pins::Inputs::Fire |
        1 << Pins::Inputs::InterlockEnable |
        1 << Pins::Inputs::OverTemp;

    constexpr static uint8_t pullups = 
        1 << Pins::Inputs::InterlockEnable |
        1 << Pins::Inputs::OverTemp;

    Pins::Inputs::Port.DIR = ~inputs;

    // Configure inputs as follows: invert polarity and configure
    // the interrupt on the leading edge.
    Pins::Inputs::Port.PINCONFIG = PORT_INVEN_bm | PORT_ISC_RISING_gc;
    Pins::Inputs::Port.PINCTRLUPD = inputs;

    // Pins that are not using hardware debounce need to be marked as pullups.
    Pins::Inputs::Port.PINCONFIG = PORT_PULLUPEN_bm;
    Pins::Inputs::Port.PINCTRLSET = pullups;

    // Clear all interrupts.
    Pins::Inputs::Port.INTFLAGS = 0xff;

    uint8_t initialState = (Pins::Inputs::Port.IN & inputs);

    _state.Interlock = PIN_HIGH(initialState, Pins::Inputs::InterlockEnable);
    _state.Temp = PIN_HIGH(initialState, Pins::Inputs::OverTemp);
    _state.Select = false;
    _state.Fire = false;
    _encoderDir = 0;

    // Hardware hacks
    pinMode(Pins::Inputs::InterlockEnableHH, INPUT_PULLUP);
    pinMode(Pins::Inputs::OverTempHH, INPUT_PULLUP);
}

void Input::processInterrupt()
{
    uint8_t interruptState = Pins::Inputs::Port.INTFLAGS;
    uint8_t pinState = Pins::Inputs::Port.IN;

    if (interruptState == 0)
    {
        // IRQ pin going back to low -- ignore.
        return;
    }

    // For the encoder position: check the pin that changed
    // and if the other pin is high, we have a confirmed change
    
    if (PIN_HIGH(interruptState, Pins::Inputs::EncoderA))
    {
        if (PIN_HIGH(pinState, Pins::Inputs::EncoderB))
        {
            _encoderDir++;
        }
    }
    else if (PIN_HIGH(interruptState, Pins::Inputs::EncoderB))
    {
        if (PIN_HIGH(pinState, Pins::Inputs::EncoderA))
        {
            _encoderDir--;
        }
    }

    // And the rest of the button states. Changes that are momentary
    // use the interrupt state.  Changes that depend on a switch remaining
    // closed use pinState.

    _state.Select = PIN_HIGH(interruptState, Pins::Inputs::EncoderSel);
    _state.Interlock = PIN_HIGH(pinState, Pins::Inputs::InterlockEnable);
    _state.Temp = PIN_HIGH(pinState, Pins::Inputs::OverTemp);

    if (PIN_HIGH(interruptState, Pins::Inputs::Fire))
    {
        _state.Fire = !_state.Fire;
    }

    // Clear the interrupt state
    Pins::Inputs::Port.INTFLAGS = 0xff;
}
