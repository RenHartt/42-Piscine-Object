#include "List.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Room.hpp"

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

void StudentList::printItem(Student* item) {
    std::cout << " - " << item->getName() << std::endl;
}

void CourseList::printItem(Course* item) {
    std::cout << " - " << item->getName() << std::endl;
    if (item->getProfessor() == nullptr) {
        std::cout << "Professor: None" << std::endl;
    } else {
        std::cout << "Professor -> " << item->getProfessor()->getName() << std::endl;
    }
    if (item->getStudents().empty()) {
        std::cout << "Student:" << std::endl;
        std::cout << "None" << std::endl;
    } else {
        std::cout << "Students: " << std::endl;
        for (const auto& student : item->getStudents()) {
            std::cout << " - " << student->getName() << std::endl;
        }
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
    } else {
        std::cout << " - Room [" << roomId << "]" << std::endl;
    }
    if (item->getOccupants().empty()) {
        std::cout << "Occupants: None" << std::endl;
    } else {
        std::cout << "Occupants: " << std::endl;
        for (const auto& occupant : item->getOccupants()) {
            std::cout << " - " << occupant->getName() << std::endl;
        }
    }
}