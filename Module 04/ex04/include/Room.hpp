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

	virtual bool canEnter(Person* person) = 0;
	void enter(Person* person) { if (canEnter(person)) { _occupants.insert(person); } }
	void exit(Person* person) { _occupants.erase(person); }
	
};

class Classroom : public Room
{
private:
	Course* _currentRoom = nullptr;

public:
	Classroom(Course* p_course = nullptr) : Room(), _currentRoom(p_course) {}
	~Classroom() {}

	Course* getCurrentCourse() const { return _currentRoom; }
	bool canEnter(Person* person) override;

	void assignCourse(Course* p_course) { _currentRoom = p_course; }
};

class StaffRestRoom : public Room, public Singleton<StaffRestRoom>
{
private:
	StaffRestRoom() : Room() {}
public:
	friend class Singleton<StaffRestRoom>;

	bool canEnter(Person* person) override;
};

class Courtyard : public Room, public Singleton<Courtyard>
{
private:
	Courtyard() : Room() {}
public:
	friend class Singleton<Courtyard>;

	bool canEnter(Person* person) override;
};

class SecretarialOffice: public Room, public Singleton<SecretarialOffice>
{
private:
	std::set<Form*> _archivedForms;
	SecretarialOffice() : Room() {}
public:
	friend class Singleton<SecretarialOffice>;

	bool canEnter(Person* person) override;
};

class HeadmasterOffice : public Room, public Singleton<HeadmasterOffice>
{
private:
	HeadmasterOffice() : Room() {}
public:
	friend class Singleton<HeadmasterOffice>;

	bool canEnter(Person* person) override;
};