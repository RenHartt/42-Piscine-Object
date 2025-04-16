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
    long long roomId = item->getID();
    if (Classroom* classroom = dynamic_cast<Classroom*>(item)) {
        std::cout << " - Classroom [" << roomId << "]" << std::endl;
        if (classroom->getCurrentCourse() == nullptr) {
            std::cout << "Current Course: None" << std::endl;
        } else {
            std::cout << "Current Course -> " << classroom->getCurrentCourse()->getName() << std::endl;
        }
    } else if (SecretarialOffice* office = dynamic_cast<SecretarialOffice*>(item)) {
        std::cout << " - Secretarial Office [" << roomId << "]" << std::endl;
    } else if (HeadmasterOffice* office = dynamic_cast<HeadmasterOffice*>(item)) {
        std::cout << " - Headmaster Office [" << roomId << "]" << std::endl;
    } else if (StaffRestRoom* restRoom = dynamic_cast<StaffRestRoom*>(item)) {
        std::cout << " - Staff Rest Room [" << roomId << "]" << std::endl;
    } else if (Courtyard* courtyard = dynamic_cast<Courtyard*>(item)) {
        std::cout << " - Courtyard [" << roomId << "]" << std::endl;
    } else {
        std::cout << " - Room [" << roomId << "]" << std::endl;
    }
    if (item->getOccupants().empty()) {
        std::cout << "Occupants: None" << std::endl;
    } else {
        std::cout << "Occupants: ";
        for (const auto& occupant : item->getOccupants()) {
            std::cout << occupant->getName() << " " << std::endl;
        }
    }
}