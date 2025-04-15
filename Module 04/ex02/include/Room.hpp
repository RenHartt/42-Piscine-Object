#pragma once

#include <set>

#include "List.hpp"

class Person;
class Course;
class Form;

class Room
{
protected:
	long long ID;
	static long long _nextID;
	static std::set<long long> _freeIDs;
	std::set<Person*> _occupants;

	long long generateID();
	void freeID(long long id);

public:
	Room() : ID(generateID()) {
		RoomList::getInstance().addToList(this);
	}
    virtual ~Room() {}

	long long getID() const { return ID; }
	const std::set<Person*>& getOccupants() const { return _occupants; }

	void printOccupant() const ;

	bool canEnter(Person*) { return true; }
	void enter(Person* person) { if (canEnter(person)) { _occupants.insert(person); } }
	void exit(Person* person) { _occupants.erase(person); }
	
};

class Classroom : public Room
{
private:
	Course* _currentRoom = nullptr;

public:
	Classroom(Course* p_course = nullptr) : _currentRoom(p_course) {}
	~Classroom() {}

	const Course* getCurrentCourse() const { return _currentRoom; }

	void assignCourse(Course* p_course) { _currentRoom = p_course; }
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