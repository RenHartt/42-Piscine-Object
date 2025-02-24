#pragma once

#include <iostream>

class Transmission {
    public:
        void shift_gear_up() { std::cout << "Car increase gear level" << std::endl; }
        void shift_gear_down() { std::cout << "Car decrease gear level" << std::endl; }
        void reverse() { std::cout << "Car set reverse gear" << std::endl; }
};