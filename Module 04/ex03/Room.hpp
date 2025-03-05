#pragma once

#include <set>
#include <memory>
#include <iostream>

class Person;
class Course;

class Room {
    private:
    long long ID;
    std::set<std::shared_ptr<Person>> _occupants;
    
    public:
    Room() {}
    virtual ~Room() {}
    
    bool canEnter(std::shared_ptr<Person> person) { return true; }
    void enter(std::shared_ptr<Person> person) { _occupants.insert(person); }
    void exit(std::shared_ptr<Person> person) { _occupants.erase(person); }
    void printOccupant() {
        for (const auto& _occupant : _occupants) {
            std::cout << _occupant << std::endl;
		}
	}
};

class Classroom : public Room {
    private:
    std::shared_ptr<Course> _currentCourse;
    
    public:
    void assignCourse(std::shared_ptr<Course> p_course) { _currentCourse = p_course; }
};

class SecretarialOffice : public Room {};
class HeadmasterOffice : public Room {};
class StaffRestRoom : public Room {};
class Courtyard : public Room {};