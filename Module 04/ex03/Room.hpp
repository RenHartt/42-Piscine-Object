#pragma once

#include <set>

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

	void printOccupant();
	bool canEnter(Person* person);
	void enter(Person* person);
	void exit(Person* person);
	
};

class Classroom : public Room
{
private:
	Course* _currentRoom = nullptr;

public:
	Classroom(Course* p_course = nullptr) : _currentRoom(p_course) {}
	~Classroom() {}

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