#pragma once

#include "DAE.hpp"

class SteerWheel {
    private:
        DAE* dae;
    public:
        SteerWheel() = default;
        void turn(float p_angle);
};