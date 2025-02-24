#pragma once

#include "Engine.hpp"
#include "Transmission.hpp"
#include "Wheel.hpp"
#include "Brake.hpp"

class Car {
    private:
        Engine engine;
        Transmission transmission;
        Wheel wheel;
        Brake brake;
    public:
        void start() { engine.start(); }
        void stop() { engine.stop(); }
        void accelerate(float speed) { engine.accelerate(speed); }
        void shiftGearsUp() { transmission.shift_gear_up(); }
        void shiftGearsDown() { transmission.shift_gear_down(); }
        void reverse() { transmission.reverse(); }
        void turnWheel(float angle) { wheel.turn_wheel(angle); }
        void straightenWheels() { wheel.straighten_wheels(); }
        void applyForceOnBrakes(float force) { brake.apply_force_on_brakes(force); }
        void applyEmergencyBrakes() { brake.apply_emergency_brakes(); }
};