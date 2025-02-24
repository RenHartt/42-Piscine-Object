#pragma once

#include "LinkablePart.hpp"
#include "ExplosionChamber.hpp"

class Injector : public LinkablePart {
    private:
        ExplosionChamber* explosionChamber;
    public:
        Injector() = default;
        void execute(float p_pression);
};