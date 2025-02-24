#pragma once

#include <iostream>

class Engine {
    public:
        void start() { std::cout << "Start Car" << std::endl; }
        void stop() { std::cout << "Stop Car" << std::endl; }
        void accelerate(float speed) { std::cout << "Car accelerate with a speed of " + std::to_string(speed) << std::endl; }
};