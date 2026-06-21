
#include "globals.h"
#include "config.h"

#define PIN_HIGH(state, pin) ((state & (1 << pin)) != 0)
#define FIRE_ENABLE_DELAY 500
#define FIRE_DISABLE_DELAY 100

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

uint8_t Input::getEncoderVelocity()
{
    // _encoderMillis is a snapshot of millis() taken
    // when the encoder changed, with the most recent sample
    // at index 0. Walk these, computing the average delta
    // between them. If any values are reversed (so n-1 > n),
    // the timer has rolled over and we just skip that value. 

    cli();
    uint16_t delta = 0;
    size_t deltaCount = 0;
    for (size_t idx = 0; idx < c_encoderMillisCount - 1; idx++)
    {
        if (_encoderMillis[idx] > _encoderMillis[idx + 1])
        {
            delta += (_encoderMillis[idx] - _encoderMillis[idx + 1]);
            deltaCount++;
        }
    }
    delta /= deltaCount;
    sei();

    constexpr uint16_t velocityValues[] =
    {
        10, 30, 50, 80, 100, 110, 120, 130, 140, 150
    };

    constexpr uint8_t velocityCount = sizeof(velocityValues) / sizeof(velocityValues[0]);

    for (uint8_t velocity = 0; velocity < velocityCount; velocity++)
    {
        if (delta <= velocityValues[velocity])
        {
            return velocityCount - velocity;
        }
    }

    return 1;
}

bool Input::getEncoderSelect()
{
    bool sel = _state.Select;
    _state.Select = false;
    return sel;
}

bool Input::getFireSwitch()
{
    if (_fireMillis != 0 &&
        millis() - _fireMillis >= (_state.Fire ? FIRE_DISABLE_DELAY : FIRE_ENABLE_DELAY))
    {
        if (PIN_HIGH(Pins::Inputs::Port.IN, Pins::Inputs::Fire))
        {
            _state.Fire = !_state.Fire;
        }
        _fireMillis = 0;
    }

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
    // the interrupt on both edges.
    Pins::Inputs::Port.PINCONFIG = PORT_INVEN_bm | PORT_ISC_BOTHEDGES_gc;
    Pins::Inputs::Port.PINCTRLUPD = inputs;

    // All inputs use Schmitt triggers
    Pins::Inputs::Port.PINCONFIG = PORT_INLVL_bm;
    Pins::Inputs::Port.PINCTRLCLR = inputs;

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
    _fireMillis = 0;
    _encoderDir = 0;

    for (size_t idx = 0; idx < c_encoderMillisCount; idx++)
    {
        _encoderMillis[idx] = 0;
    }
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

    // We listen to both rising and falling edges to capture
    // temp and interlock transitions. But we really only
    // care about rising edges for interrupts. 

    interruptState &= pinState;

    // For the encoder position: check the pin that changed
    // and if the other pin is high, we have a confirmed change
    
    bool updateEncoderMillis = false;
    
    if (PIN_HIGH(interruptState, Pins::Inputs::EncoderA))
    {
        if (PIN_HIGH(pinState, Pins::Inputs::EncoderB))
        {
            _encoderDir++;
            updateEncoderMillis = true;
        }
    }
    else if (PIN_HIGH(interruptState, Pins::Inputs::EncoderB))
    {
        if (PIN_HIGH(pinState, Pins::Inputs::EncoderA))
        {
            _encoderDir--;
            updateEncoderMillis = true;
        }
    }

    if (updateEncoderMillis)
    {
        for (size_t idx = c_encoderMillisCount - 1; idx > 0; idx--)
        {
            _encoderMillis[idx] = _encoderMillis[idx - 1];
        }
        _encoderMillis[0] = millis();
    }

    // And the rest of the button states. Changes that are momentary
    // use the interrupt state.  Changes that depend on a switch remaining
    // closed use pinState.

    _state.Select = PIN_HIGH(interruptState, Pins::Inputs::EncoderSel);
    _state.Interlock = PIN_HIGH(pinState, Pins::Inputs::InterlockEnable);
    _state.Temp = PIN_HIGH(pinState, Pins::Inputs::OverTemp);

    // For the fire button, require it to be pressed for a bit before
    // changing state.

    if (PIN_HIGH(interruptState, Pins::Inputs::Fire))
    {
        _fireMillis = millis();
    }

    // Clear the interrupt state
    Pins::Inputs::Port.INTFLAGS = 0xff;
}
