#pragma once

#include "Injector.hpp"
#include "ExplosionChamber.hpp"
#include "Crankshaft.hpp"
#include "Transmission.hpp"

class Motor {
    private:
        Injector injector;
        ExplosionChamber explosionChamber;
        Crankshaft crankshaft;
    public:
        Motor();
        void connectToTransmission(Transmission* p_transmission);
};