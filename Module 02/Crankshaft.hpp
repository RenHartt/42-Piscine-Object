#pragma once

#include "Transmission.hpp"

class Crankshaft {
    private:
        Transmission transmission;
    public:
        Crankshaft() = default;    
        void receiveForce(float p_volume);
};