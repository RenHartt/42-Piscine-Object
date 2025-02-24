#pragma once

#include <iostream>

class Brake {
    public:
        void apply_force_on_brakes(float force) { std::cout << "Car brake with a force of " + std::to_string(force) << std::endl; }
        void apply_emergency_brakes() { std::cout << "Car launch emergency brake" << std::endl; }
};