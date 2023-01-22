
#include "globals.h"
#include "config.h"

#define PIN_HIGH(state, pin) ((state & pin) != 0)

#define DEBOUNCE_TIME 40
#define PENDING_RESET_TIME 125

Input::Input() :
    _gpio(Pins::Gpio::Cs)
{
    pinMode(Pins::Gpio::Irq, INPUT_PULLUP);
}

int8_t Input::getEncoderDirection()
{
    if (_encoderData.pending && millis() - _encoderData.timestamp > DEBOUNCE_TIME)
    {
        _encoderDir += (_encoderData.ccw ? -1 : 1);
        _encoderData.pending = 0;
    }

    int8_t dir = _encoderDir;
    _encoderDir = 0;
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
    return _state.Interlock;
}

bool Input::getOverTemp()
{
    return _state.Temp;
}

void Input::toggleFireSwitch()
{
    _state.Fire = !_state.Fire;
}

void Input::setFireSwitchLed(bool on)
{
    uint8_t state = _gpio.getPinState();

    if (on)
    {
        state |= Pins::Gpio::Outputs::FireLed;
    }
    else
    {
        state &= ~Pins::Gpio::Outputs::FireLed;
    }

    _gpio.setPinState(state);
}

void Input::reset()
{
    // Configure inputs / outputs
    constexpr static uint8_t inputs =
        Pins::Gpio::Inputs::EncoderA |
        Pins::Gpio::Inputs::EncoderB |
        Pins::Gpio::Inputs::EncoderSel |
        Pins::Gpio::Inputs::FireMom |
        Pins::Gpio::Inputs::FireLatch |
        Pins::Gpio::Inputs::InterlockEnable |
        Pins::Gpio::Inputs::OverTemp;

    constexpr static uint8_t outputs =
        Pins::Gpio::Outputs::FireLed;

    _gpio.setDirection(inputs);

    // These are directly tied to our IO bus. Use a pullup to ensure
    // they don't float if the bus isn't connected. The encoder switches
    // do not go through the debounce chip because it is too slow, so
    // these need pullups too.

    _gpio.setPullups(Pins::Gpio::Inputs::InterlockEnable |
                     Pins::Gpio::Inputs::OverTemp |
                     Pins::Gpio::Inputs::EncoderA |
                     Pins::Gpio::Inputs::EncoderB);

    // All inputs are active low. Invert the results to make
    // checking simpler.

    _gpio.invertPolarity(inputs);

    // Enable input filtering in everything but the interlock. If
    // it bounces we want to know.

    _gpio.enableInputFilter(~Pins::Gpio::Inputs::InterlockEnable);

    // Note: no input pullups are needed because buttons are sent
    // through a debounce chip, and it provides its own pullups and
    // provides a clean signal.

    _gpio.setInterrupts(inputs);

    // Falling / rising edges are based no physical signals and
    // do not change for pins with inverted polarity, so a press
    // down is a falling edge, and a release is a rising edge.

    uint8_t fallingEdgeInterrupts = inputs;
    uint8_t risingEdgeInterrupts =
        Pins::Gpio::Inputs::FireMom |
        Pins::Gpio::Inputs::InterlockEnable |
        Pins::Gpio::Inputs::OverTemp;

    _gpio.setRisingEdgeInterrupts(risingEdgeInterrupts);
    _gpio.setFallingEdgeInterrupts(fallingEdgeInterrupts);

    uint8_t initialState = _gpio.getPinState();
    initialState &= ~outputs;
    _gpio.setPinState(initialState);

    _state.Interlock = PIN_HIGH(initialState, Pins::Gpio::Inputs::InterlockEnable);
    _state.Temp = PIN_HIGH(initialState, Pins::Gpio::Inputs::OverTemp);
    _state.Select = false;
    _state.Fire = false;
    _encoderDir = 0;
    _encoderData.pending = 0;
}

void Input::processInterrupt()
{
    uint8_t interruptState = _gpio.getInterruptState();
    uint8_t pinState = _gpio.getPinState();

    if (interruptState == 0)
    {
        // IRQ pin going back to low -- ignore.
        return;
    }

    // Calculate new encoder position. Quadature encoding has
    // a specific pattern of A and B that changes based on 
    // the turn direction. The interrupt on the GPIO chip
    // is programmed to only fire on falling transitions,
    // so we can filter out transitions to ignore easily.

    constexpr static auto ab = Pins::Gpio::Inputs::EncoderA | Pins::Gpio::Inputs::EncoderB;

    // Encoder does not flow through our debounce hardware
    // because it is too slow (80ms debounce time for both 
    // open and close). So do a simple debounce in software
    // here by recording the timestamp of the encoder data.
    // If we see another pending entry that is faster than
    // our debounce time we can throw it away.

    if ((interruptState & ab) != 0)
    {
        uint32_t timestamp = millis();

        // Throw away pending data if we are past our pending reset time
        if (timestamp - _encoderData.timestamp > PENDING_RESET_TIME)
        {
            _encoderData.pending = 0;
        }

        if (!_encoderData.pending || timestamp - _encoderData.timestamp > DEBOUNCE_TIME)
        {
            if (_encoderData.pending)
            {
                _encoderDir += (_encoderData.ccw ? -1 : 1);
                _encoderData.pending = 0;
            }

            uint8_t encoderState = pinState & ab;
            if (encoderState == Pins::Gpio::Inputs::EncoderA)
            {
                _encoderData.ccw = true;
                _encoderData.pending = true;
            }
            else if (encoderState == Pins::Gpio::Inputs::EncoderB)
            {
                _encoderData.ccw = false;
                _encoderData.pending = true;
            }

            _encoderData.timestamp = timestamp;
        }
    }

    // And the rest of the button states. Changes that are momentary
    // use the interrupt state.  Changes that depend on a switch remaining
    // closed use pinState.

    _state.Select = PIN_HIGH(interruptState, Pins::Gpio::Inputs::EncoderSel);
    _state.Interlock = PIN_HIGH(pinState, Pins::Gpio::Inputs::InterlockEnable);
    _state.Temp = PIN_HIGH(pinState, Pins::Gpio::Inputs::OverTemp);

    if (PIN_HIGH(interruptState, Pins::Gpio::Inputs::FireLatch))
    {
        _state.Fire = !_state.Fire;
    }
    else if (PIN_HIGH(interruptState, Pins::Gpio::Inputs::FireMom))
    {
        _state.Fire = PIN_HIGH(pinState, Pins::Gpio::Inputs::FireMom);
    }
}
