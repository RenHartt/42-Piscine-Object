#pragma once

#include <vector>
#include "Wheel.hpp"

class Transmission {
    private:
        std::vector<Wheel *> wheels;
    public:
        Transmission() = default;
        void activate(float p_force);
};