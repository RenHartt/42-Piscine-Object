#pragma once

#include <set>

#include "Person.hpp"
#include "Course.hpp"

class Room
{
private:
	long long ID;
	std::set<std::weak_ptr<Person>> _occupants;

public:
	Room();
    virtual ~Room();
	bool canEnter(std::shared_ptr<Person> person);
	void enter(std::shared_ptr<Person> person);
	void exit(std::shared_ptr<Person> person);
	
	void printOccupant();
};

class Classroom : public Room
{
private:
	std::shared_ptr<Course> _currentRoom;

public:
	Classroom();
	void assignCourse(std::shared_ptr<Course> p_course);
};

class SecretarialOffice: public Room
{
private:
	std::set<std::shared_ptr<Form>> _archivedForms;

public:

};

class HeadmasterOffice : public Room
{
private:

public:

};

class StaffRestRoom : public Room
{
private:

public:

};

class Courtyard : public Room
{
private:

public:

};