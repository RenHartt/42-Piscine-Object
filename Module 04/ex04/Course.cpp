#include "Course.hpp"
#include "Person.hpp"

#include <iostream>

Course::Course(std::string p_name): _name(p_name), _responsable(nullptr) {}

std::string Course::getName() const { return _name; }

void Course::assign(std::shared_ptr<Professor> p_professor) { _responsable = p_professor; }

void Course::subscribe(std::shared_ptr<Student> p_student) {
    if (_students.size() >= _maximumNumberOfStudent) {
        std::cerr << "Course " << _name << " is full! Cannot subscribe " << p_student->getName() << ".\n";
        return;
    }
    if (_students.insert(p_student).second) {
        std::cout << p_student->getName() << " has been enrolled in " << _name << ".\n";
    } else {
        std::cerr << p_student->getName() << " is already enrolled in " << _name << ".\n";
    }
}

void Course::graduateStudent(std::shared_ptr<Student> p_student) {
    if (_students.erase(p_student) > 0) {
        std::cout << p_student->getName() << " has successfully graduated from " << _name << "!\n";
    } else {
        std::cerr << p_student->getName() << " was not found in " << _name << ".\n";
    }
}
