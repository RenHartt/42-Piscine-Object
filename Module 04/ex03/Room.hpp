#pragma once

#include <set>
#include <iostream>

class Person;
class Course;
class Form;

class Room
{
private:
	long long ID = 0;
	std::set<Person*> _occupants;

public:
	Room(long long p_id = 0) : ID(p_id) {}
    virtual ~Room() {}

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
	Course* _currentRoom = nullptr;

public:
	Classroom(Course* p_course = nullptr) : _currentRoom(p_course) {}
	~Classroom() {}

	void assignCourse(Course* p_course) { _currentRoom = p_course; }
	Course* getCourse() const { return _currentRoom; }
	bool canEnter(Person* person) override { return _currentRoom->getMaximumNumberOfStudent() > _currentRoom->getStudents().size(); }
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
	HeadmasterOffice() {}
	~HeadmasterOffice() {}
};

class StaffRestRoom : public Room
{
private:

public:
	StaffRestRoom() {}
	~StaffRestRoom() {}
};

class Courtyard : public Room
{
private:

public:
	Courtyard() {}
	~Courtyard() {}
};