#pragma once

#include <string>
#include <set>
#include <memory>

#include "Room.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Form.hpp"

class Person
{
private:
	std::string _name;
	std::weak_ptr<Room> _currentRoom;
public:
	Person(std::string p_name);
    virtual ~Person();
	std::shared_ptr<Room> room() {return (_currentRoom.lock());}
};

class Staff : public Person
{
private:

public:
	void sign(std::shared_ptr<Form> p_form);
};

class Student : public Person
{
private:
	std::set<std::shared_ptr<Course>> _subscribedCourse;

public:
	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(std::shared_ptr<Course> p_course);
};

class Headmaster : public Staff
{
private:
	std::set<std::shared_ptr<Form>> _formToValidate;
	
public:
	void receiveForm(std::shared_ptr<Form> p_form);
};

class Secretary : public Staff
{
private:

public:
	std::shared_ptr<Form> createForm(FormType p_formType);
	void archiveForm();
};

class Professor : public Staff
{
private:
	std::shared_ptr<Course> _currentCourse;

public:
	void assignCourse(std::shared_ptr<Course> p_course);
	void doClass();
	void closeCourse();
};
