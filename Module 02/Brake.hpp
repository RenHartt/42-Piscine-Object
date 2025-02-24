#pragma once

#include "Wheel.hpp"

class Brake {
    private:
        Wheel* wheel;
    public:
        Brake() = default;
        void execute(float p_force);
        void attackWheel(Wheel* p_wheel);
};