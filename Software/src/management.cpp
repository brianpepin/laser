#include "globals.h"
#include "macros.h"
#include "management.h"
#include "config.h"
#include "console.h"
#include "led.h"
#include "power.h"
#include "views/battery.h"
#include "views/menu.h"
#include "views/running.h"

namespace Management
{
    struct Flags
    {
        uint8_t enabled : 1;
        uint8_t criticalBattery : 1;
    };

    static View* _currentView = nullptr;
    static View* _activeView = nullptr;
    static SystemStatus _systemStatus{};
    static Flags _flags{};
    static Power _power;
    static uint32_t _millis = 0;

    namespace Views
    {
        static BatteryView battery;
        static RunningView running;
        static MenuView menu;
    }

    static View* _views[]
    {
        &Views::running,
        &Views::battery,
        &Views::menu
    };

    void updateSystemStatus()
    {
        _systemStatus.laser = laser.getStatus();
        _systemStatus.tec = tec.getStatus();
        _systemStatus.power = _power.getStatus();

        _systemStatus.ok =
            _systemStatus.laser.ok &&
            _systemStatus.tec.ok;

        if (!input.getInterlockSwitch())
        {
            enable(false);
        }

        if (_systemStatus.power.batteryVoltage > Limits::Voltage::LowBat)
        {
            _flags.criticalBattery = false;
        }
        else if (_systemStatus.power.batteryVoltage < Limits::Voltage::CriticalBat)
        {
            _flags.criticalBattery = true;
        }
    }

    View* getView()
    {
        if (!input.getInterlockSwitch() ||
            _flags.criticalBattery)
        {
            return getView(ViewId::Battery);
        }

        if (_currentView == nullptr)
        {
            _currentView = getView(ViewId::Default);
        }
        
        return _currentView;
    }

    bool switchView(View* newView)
    {
        if (newView == _activeView)
        {
            return false;
        }

        View* previousView = _activeView;

        if (previousView != nullptr)
        {
            previousView->stop();
        }

        _activeView = newView;

        if (newView != nullptr)
        {
            newView->start(previousView);
        }

        return true;
    }

    View* getView(ViewId id)
    {
        return _views[static_cast<int>(id)];
    }

    const SystemStatus& getSystemStatus()
    {
        return _systemStatus;
    }

    void enable(bool enable, bool force)
    {
        if (enable && ((!_flags.enabled && input.getInterlockSwitch()) || force))
        {
            laser.reset();

            tec.enable(false);

            tec.setTemp(Tec::Channel::Pump1, settings.temps.pump1);
            tec.setCurrent(Tec::Channel::Pump1, Defaults::Currents::Tec::Pump);

            tec.setTemp(Tec::Channel::Pump2, settings.temps.pump2);
            tec.setCurrent(Tec::Channel::Pump2, Defaults::Currents::Tec::Pump);

            tec.setTemp(Tec::Channel::Vanadate, settings.temps.vanadate);
            tec.setCurrent(Tec::Channel::Vanadate, Defaults::Currents::Tec::Vanadate);

            tec.setTemp(Tec::Channel::Ktp, settings.temps.ktp);
            tec.setCurrent(Tec::Channel::Ktp, Defaults::Currents::Tec::Ktp);

            tec.enable(true);
            input.reset();

            _flags.enabled = true;
            updateSystemStatus();
        }
        else if(!enable && (_flags.enabled || force))
        {
            laser.reset();
            input.reset();
            tec.enable(false);
            _flags.enabled = false;
        }
    }

    //
    // Used during debugging to set parameters of the status.
    // Calling this with a non-null status will enter simulation
    // mode for this and all subsystems. In simulation mode, laser
    // power output tracks input requests. Calling this with null
    // ends the simulation. To change simulation values call
    // setSimulation again.
    //
    void setSimulation(const SystemStatus* simulatedStatus)
    {
        if (simulatedStatus != nullptr)
        {
            laser.setSimulation(&simulatedStatus->laser);
            tec.setSimulation(&simulatedStatus->tec);
            _power.setSimulation(&simulatedStatus->power);
        }
        else
        {
            laser.setSimulation(nullptr);
            tec.setSimulation(nullptr);
            _power.setSimulation(nullptr);
        }
    }

    void restart()
    {
        if (_flags.enabled)
        {
            enable(false);
            enable(true);
        }
    }

    void tick()
    {
        uint32_t m = millis();
        if (m - _millis > 10)
        {
            updateSystemStatus();
            _millis = m;
        }

        bool update = switchView(getView());

        View* newView = nullptr;
        update |= _activeView->tick(&newView);

        if (newView != nullptr)
        {
            _currentView = newView;
            update |= switchView(newView);
            newView = nullptr;
        }

        if (_activeView != &Views::battery)
        {
            update |= Views::battery.tick(&newView);
        }

        led.setCharging(_systemStatus.power.batteryCharging);
        led.setInterlock(input.getInterlockSwitch());
        led.setCriticalBattery(_flags.criticalBattery);
        led.setError(_flags.enabled && !_systemStatus.ok);
        led.setFiring(_flags.enabled && (_systemStatus.laser.led1.enabled || _systemStatus.laser.led2.enabled));

        led.tick();
        laser.tick();
        _power.tick();
        Console::tick();

        if (update)
        {
            display.firstPage();

            do
            {
                _activeView->render();

                if (_activeView != &Views::battery)
                {
                    Views::battery.renderOverlay();
                }

            } while (display.nextPage());
        }
    }
}