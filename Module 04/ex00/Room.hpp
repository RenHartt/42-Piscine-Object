#pragma once

#include <set>

class Person;
class Course;
class Form;

class Room
{
private:
	long long ID;
	std::set<Person*> _occupants;

public:
	Room();
    virtual ~Room();
	bool canEnter(Person* person);
	void enter(Person* person);
	void exit(Person* person);
	
	void printOccupant();
};

class Classroom : public Room
{
private:
	Course* _currentRoom;

public:
	Classroom();
	void assignCourse(Course* p_course);
};

class SecretarialOffice: public Room
{
private:
	std::set<Form*> _archivedForms;

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