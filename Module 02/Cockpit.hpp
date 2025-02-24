#pragma once

#include "Pedal.hpp"
#include "SteerWheel.hpp"
#include "GearLever.hpp"

class Cockpit {
    private:
        Pedal pedal;
        SteerWheel steerWheel;
        GearLever& gearLever;
    public:
        Cockpit();
};