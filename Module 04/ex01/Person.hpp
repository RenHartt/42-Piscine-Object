#pragma once

#include <string>
#include <vector>
#include <memory>

class Room;
class Form;
class Course;
class Classroom;
enum class FormType;

class Person
{
private:
	std::string _name;
	Room* _currentRoom;
public:
	Person(std::string p_name): _name(p_name) {}

	const std::string& getName() const { return _name; }

	Room* room() { return _currentRoom; }
};

class Staff : public Person
{
private:

public:
	Staff(const std::string& name): Person(name) {}

	void sign(Form* p_form);
};

class Student : public Person
{
private:
	std::vector<Course*> _subscribedCourse;

public:
	Student(const std::string& name): Person(name) {}

	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(Course* p_course);
};

class Headmaster : public Staff
{
private:
	std::vector<Form*> _formToValidate;
	
public:
	Headmaster(const std::string& name): Staff(name) {}

	void receiveForm(Form* p_form);
};

class Secretary : public Staff
{
private:

public:
	Secretary(const std::string& name): Staff(name) {}

	Form* createForm(FormType p_formType);
	void archiveForm();
};

class Professor : public Staff
{
private:
	Course* _currentCourse;

public:
	Professor(const std::string& name): Staff(name) {}

	void assignCourse(Course* p_course);
	void doClass();
	void closeCourse();
};
