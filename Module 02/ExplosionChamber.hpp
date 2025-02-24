#pragma once

#include "Crankshaft.hpp"

class ExplosionChamber {
    private:
        Crankshaft* crankshaft;
    public:
        ExplosionChamber() = default;
        void fill(float p_volume);
};