#include "List.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Room.hpp"

StudentList::~StudentList() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& item : list) {
        delete item;
    }
}

void StudentList::printItem(Student* item) {
    std::cout << item->getName() << std::endl;
}

StaffList::~StaffList() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& item : getProfessors()) {
        delete item;
    }
}

std::set<Professor*> StaffList::getProfessors() {
    std::set<Professor*> professors;
    for (const auto& item : list) {
        if (Professor* professor = dynamic_cast<Professor*>(item)) {
            professors.insert(professor);
        }
    }
    return professors;
}

void StaffList::printItem(Staff* item) {
    std::cout << item->getName() << std::endl;
}

CourseList::~CourseList() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& item : list) {
        delete item;
    }
}

void CourseList::printItem(Course* item) {
    std::cout << item->getName() << std::endl;
    if (item->getProfessor() == nullptr) {
        std::cout << "Professor: None" << std::endl;
    } else {
        std::cout << "Professor: " << item->getProfessor()->getName() << std::endl;
    }
    if (item->getStudents().empty()) {
        std::cout << "Student: None" << std::endl;
    } else {
        std::cout << "Students: " << std::endl;
        for (const auto& student : item->getStudents()) {
            std::cout << student->getName() << std::endl;
        }
    }
}

std::set<Classroom*> RoomList::getClassrooms() {
    std::set<Classroom*> classrooms;
    for (const auto& item : list) {
        if (Classroom* classroom = dynamic_cast<Classroom*>(item)) {
            classrooms.insert(classroom);
        }
    }
    return classrooms;
}

RoomList::~RoomList() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& item : getClassrooms()) {
        delete item;
    }
}

void RoomList::printItem(Room* item) {
    std::cout << "Room ID: " << item->getID() << std::endl;
    std::cout << "Occupants: ";
    if (item->getOccupants().empty()) {
        std::cout << "None" << std::endl;
    } else {
        std::cout << std::endl;
        item->printOccupant();
    }
}