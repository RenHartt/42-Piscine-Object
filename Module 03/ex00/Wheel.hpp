#pragma once

#include <iostream>

class Wheel {
    public:
        void turn_wheel(float angle) { std::cout << "Car turn wheel with an angle of " + std::to_string(angle) << std::endl; }
        void straighten_wheels() { std::cout << "Car reset wheel orientation" << std::endl; }
};