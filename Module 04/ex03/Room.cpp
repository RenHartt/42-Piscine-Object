#include "Room.hpp"
#include "Person.hpp"
#include <iostream>

void Room::printOccupant() {
    for (const auto& occupant : _occupants) {
        std::cout << occupant->getName() << std::endl;
    }
}