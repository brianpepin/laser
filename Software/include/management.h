#pragma once

#include "laser.h"
#include "tec.h"
#include "power.h"
#include "view.h"

enum class ViewId
{
    Default,
    Battery,
    Menu
};

struct SystemStatus
{
    bool ok;
    Laser::Status laser;
    Tec::Status tec;
    Power::Status power;
};

namespace Management
{
    //
    // Returns a pointer to  a view with the given ID.  Used by views
    // to navigate to other views.
    //
    View* getView(ViewId id);

    //
    // Management runs a watchdog that monitors system state with every
    // tick.  This returns a reference to the current state.
    //
    const SystemStatus& getSystemStatus();

    //
    // Global enable / disable of the system. Used as a master kill
    // if the interlock switch is turned off or if there is a temp or
    // other system problem.
    //
    void enable(bool enable, bool force = false);

    //
    // Used during debugging to set parameters of the status.
    // Calling this with a non-null status will enter simulation
    // mode for this and all subsystems. In simulation mode, laser
    // power output tracks input requests. Calling this with null
    // ends the simulation. To change simulation values call
    // setSimulation again.
    //
    void setSimulation(const SystemStatus* simulatedStatus);

    //
    // If enabled, this will perform a restart cycle.
    //
    void restart();

    //
    // Called by the render loop.  Performs all housekeeping.
    //
    void tick();
}