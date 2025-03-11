#include "Room.hpp"

Room::Room() {}
Room::~Room() {}
bool Room::canEnter(std::shared_ptr<Person> person) { return true; }
void Room::enter(std::shared_ptr<Person> person) { _occupants.insert(person); }
void Room::exit(std::shared_ptr<Person> person) { _occupants.erase(person); }
void Room::printOccupant() {
    for (const auto& _occupant : _occupants) {
        std::cout << _occupant << std::endl;
    }
}

void Classroom::assignCourse(std::shared_ptr<Course> p_course) { _currentCourse = p_course; }