#pragma once

#include <set>
#include <iostream>

#include "List.hpp"

class Person;
class Course;
class Form;

class Room
{
private:
	long long ID = 0;
	std::set<Person*> _occupants;

public:
	Room(long long p_id = 0) {
		ID = RoomList::getInstance().generateID();
		RoomList::getInstance().addToList(this);
	}
    virtual ~Room() {
		RoomList::getInstance().releaseID(ID);
	}

	long long getID() const { return ID; }
	const std::set<Person*>& getOccupants() const { return _occupants; }
	void printOccupant() {
		for (const auto& occupant : _occupants) {
			std::cout << occupant->getName() << std::endl;
		}
	}
	virtual bool canEnter(Person* person) { return true; }
	void enter(Person* person) { _occupants.insert(person); }
	void exit(Person* person) { _occupants.erase(person); }
	
};

class Classroom : public Room
{
private:
	Course* _assignedCourse = nullptr;

public:
	Classroom(Course* p_course = nullptr) : _assignedCourse(p_course) {}
	~Classroom() {}

	void assignCourse(Course* p_course) { _assignedCourse = p_course; }
	void removeCourse() { _assignedCourse = nullptr; }
	Course* assignedCourse() const { return _assignedCourse; }
	bool canEnter(Person* person) override { return _assignedCourse->maximumStudents() > _assignedCourse->getStudents().size(); }
};

class SecretarialOffice: public Room
{
private:
	std::set<Form*> _archivedForms;

public:
	SecretarialOffice() {}
	~SecretarialOffice() {}
};

class HeadmasterOffice : public Room
{
private:

public:
	HeadmasterOffice() = default;
	~HeadmasterOffice() = default;
};

class StaffRestRoom : public Room
{
private:

public:
	StaffRestRoom() = default;
	~StaffRestRoom() = default;
};

class Courtyard : public Room
{
private:

public:
	Courtyard() = default;
	~Courtyard() = default;
};