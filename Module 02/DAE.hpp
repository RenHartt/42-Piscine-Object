#pragma once

#include "Direction.hpp"

class DAE {
    private:
        Direction* direction;
        float force;
    public:
        DAE() = default;
        void use(float p_angle);
};