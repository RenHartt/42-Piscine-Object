#include "List.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Room.hpp"

StaffList::~StaffList() {
    for (const auto& professor : getProfessors()) {
        delete professor;
    }
}

Headmaster* StaffList::getHeadmaster() {
	for (const auto& staff : list) {
		if (Headmaster* h = dynamic_cast<Headmaster*>(staff))
			return h;
	}
	return nullptr;
}

Secretary* StaffList::getSecretary() {
	for (const auto& staff : list) {
		if (Secretary* s = dynamic_cast<Secretary*>(staff))
			return s;
	}
	return nullptr;
}

std::set<Professor*> StaffList::getProfessors() {
    std::set<Professor*> professors;
    for (const auto& staff : list) {
        if (Professor* p = dynamic_cast<Professor*>(staff))
            professors.insert(p);
    }
    return professors;
}

void StaffList::printItem(Staff* item) {
    std::cout << " - " << item->getName() << std::endl;
}

StudentList::~StudentList() {
    for (const auto& student : getList()) {
        delete student;
    }
}

void StudentList::printItem(Student* item) {
    std::cout << " - " << item->getName() << std::endl;
}

std::set<Classroom*> RoomList::getClassrooms() {
    std::set<Classroom*> classrooms;
    for (const auto& room : list) {
        if (Classroom* classroom = dynamic_cast<Classroom*>(room)) {
            classrooms.insert(classroom);
        }
    }
    return classrooms;
}

Classroom* RoomList::getClassroom() {
    for (const auto& room : RoomList::getInstance().getList()) {
        if (Classroom* classroom = dynamic_cast<Classroom*>(room)) {
            return classroom;
        }
    }
    return nullptr;
}

SecretarialOffice* RoomList::getSecretarialOffice() {
    for (const auto& room : RoomList::getInstance().getList()) {
        if (SecretarialOffice* office = dynamic_cast<SecretarialOffice*>(room)) {
            return office;
        }
    }
    return nullptr;
}

HeadmasterOffice* RoomList::getHeadmasterOffice() {
    for (const auto& room : RoomList::getInstance().getList()) {
        if (HeadmasterOffice* office = dynamic_cast<HeadmasterOffice*>(room)) {
            return office;
        }
    }
    return nullptr;
}

StaffRestRoom* RoomList::getStaffRestRoom() {
    for (const auto& room : RoomList::getInstance().getList()) {
        if (StaffRestRoom* restRoom = dynamic_cast<StaffRestRoom*>(room)) {
            return restRoom;
        }
    }
    return nullptr;
}  

Courtyard* RoomList::getCourtyard() {
    for (const auto& room : RoomList::getInstance().getList()) {
        if (Courtyard* courtyard = dynamic_cast<Courtyard*>(room)) {
            return courtyard;
        }
    }
    return nullptr;
}

CourseList::~CourseList() {
    for (const auto& course : getList()) {
        delete course;
    }
}

void CourseList::printItem(Course* item) {
    std::cout << " - " << item->getName() << std::endl;
    if (item->getProfessor() == nullptr) {
        std::cout << "Professor: None" << std::endl;
    } else {
        std::cout << "Professor -> " << item->getProfessor()->getName() << std::endl;
    }
    if (item->getStudents().empty()) {
        std::cout << "Students: ";
        std::cout << "None" << std::endl;
    } else {
        std::cout << "Students: ";
        for (const auto& student : item->getStudents()) {
            std::cout << student->getName() << " ";
        }
    }
}

RoomList::~RoomList() {
    for (const auto& classroom : getClassrooms()) {
        delete classroom;
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