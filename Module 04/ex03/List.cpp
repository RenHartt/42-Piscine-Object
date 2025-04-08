#include "List.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Room.hpp"

void StudentList::printItem(Student* item) {
    std::cout << item->getName() << std::endl;
}

void StaffList::printItem(Staff* item) {
    std::cout << item->getName() << std::endl;
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