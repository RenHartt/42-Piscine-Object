#pragma once

#include "LinkablePart.hpp"

class Pedal {
    private:
        LinkablePart* linkablePart = nullptr;
    public:
        Pedal() = default;
        void setTarget(LinkablePart* p_part);
        void use(float p_pression);
};