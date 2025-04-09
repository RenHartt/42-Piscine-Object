#pragma once

#include <string>
#include <set>
#include <memory>

#include "List.hpp"

class Room;
class Course;
class Classroom;
class Form;
enum class FormType;

class Person
{
private:
	std::string _name;
	Room* _currentRoom = nullptr;
public:
	Person(std::string p_name) : _name(p_name) {}
	virtual ~Person() {}

	const std::string& getName() const { return _name; }

	Room* room() { return _currentRoom; }
};

class Staff : public Person
{
private:

public:
	Staff(std::string p_name) : Person(p_name) {
		StaffList::getInstance().addToList(this);
	}
	virtual ~Staff() {}
};

class Student : public Person
{
private:
	std::set<Course*> _subscribedCourse;

public:
	Student(std::string p_name) : Person(p_name) {
		StudentList::getInstance().addToList(this);
	}
	~Student() {}

	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(Course* p_course);
};

class Headmaster : public Staff
{
private:
	std::set<Form*> _formToValidate;
	
public:
	Headmaster(std::string p_name) : Staff(p_name) {}
	~Headmaster() {}

	void sign(Form* p_form);
	void receiveForm(Form* p_form);
};

class Secretary : public Staff
{
private:

public:
	Secretary(std::string p_name) : Staff(p_name) {}
	~Secretary() {}

	Form* createForm(FormType p_formType);
	void archiveForm();
};

class Professor : public Staff
{
private:
	Course* _currentCourse = nullptr;

public:
	Professor(std::string p_name) : Staff(p_name) {}
	~Professor() {}

	void assignCourse(Course* p_course);
	void doClass();
	void closeCourse();
};
