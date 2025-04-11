#include "Room.hpp"
#include "Person.hpp"
#include "Course.hpp"

std::set<long long> Room::_freeIDs;
long long Room::_nextID = 1;

long long Room::generateID() {
    if (_freeIDs.empty() == false) {
        long long id = *_freeIDs.begin();
        _freeIDs.erase(_freeIDs.begin());
        return id;
    }
    return _nextID++;
}

void Room::freeID(long long id) {
    _freeIDs.insert(id);
}

void Room::printOccupant() const {
    for (const auto& occupant : _occupants) {
        std::cout << occupant->getName() << std::endl;
    }
}

bool Classroom::canEnter(Person* person) {
    if (_currentRoom == nullptr) {
        return false;
    } else if (this->getOccupants().size() >= _currentRoom->getMaximumNumberOfStudent()) {
        return false;
    } else {
        return true;
    }
}