#pragma once

#include <array>
#include "Wheel.hpp"

class Direction {
    private:
        std::array<Wheel, 4> wheels;
    public:
        Direction() = default;
        void turn(float p_angle);
};