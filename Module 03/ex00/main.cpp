#include <iostream>
#include "Car.hpp"

int main() {
    Car myCar;

    myCar.start();
    myCar.accelerate(30.0f);
    myCar.shiftGearsUp();
    myCar.reverse();
    myCar.turnWheel(15.0f);
    myCar.straightenWheels();
    myCar.applyForceOnBrakes(50.0f);
    myCar.applyEmergencyBrakes();
    myCar.stop();

    return 0;
}

