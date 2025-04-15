#include "Room.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Form.hpp"

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

bool Classroom::canEnter(Person*) {
    if (_currentRoom == nullptr) {
        return false;
    } else if (this->getOccupants().size() >= _currentRoom->getMaximumNumberOfStudent()) {
        return false;
    } else {
        return true;
    }
}

bool StaffRestRoom::canEnter(Person* person) {
   return dynamic_cast<Staff*>(person) != nullptr;
}

SecretarialOffice::~SecretarialOffice() {
    for (const auto& form : _archivedForms) {
        delete form;
    }
}

bool SecretarialOffice::canEnter(Person* person) {
    return dynamic_cast<Secretary*>(person) != nullptr;
}

bool HeadmasterOffice::canEnter(Person* person) {
    return dynamic_cast<Headmaster*>(person) != nullptr;
}

bool Courtyard::canEnter(Person*) {
    return true;
}