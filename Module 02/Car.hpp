#pragma once

#include "BrakeController.hpp"
#include "Direction.hpp"
#include "Transmission.hpp"
#include "Motor.hpp"
#include "Electronics.hpp"
#include "Cockpit.hpp"

class Car {
    private:
        BrakeController brakecontroller;
        Direction direction;
        Transmission transmission;
        Motor motor;
        Electronics electronics;
        Cockpit cockpit;
    public:
        Car();
};