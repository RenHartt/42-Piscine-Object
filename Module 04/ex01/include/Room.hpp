#pragma once

#include <set>

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
	Room(long long p_id = 0) : ID(p_id) {
		RoomList::getInstance().addToList(this);
	}
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

	void assignCourse(Course* p_course);
};

class SecretarialOffice: public Room, public Singleton<SecretarialOffice>
{
private:
	std::set<Form*> _archivedForms;

	SecretarialOffice() {}
public:
	friend class Singleton<SecretarialOffice>;
};

class HeadmasterOffice : public Room, public Singleton<HeadmasterOffice>
{
private:
	HeadmasterOffice() {}
public:
	friend class Singleton<HeadmasterOffice>;
};

class StaffRestRoom : public Room, public Singleton<StaffRestRoom>
{
private:
	StaffRestRoom() {}
public:
	friend class Singleton<StaffRestRoom>;
};

class Courtyard : public Room, public Singleton<Courtyard>
{
private:
	Courtyard() {}
public:
	friend class Singleton<Courtyard>;
};