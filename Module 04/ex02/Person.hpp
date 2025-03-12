#pragma once

#include <string>
#include <set>
#include <vector>

enum class FormType;
class Form;
class Classroom;
class Student;
class Staff;
class Course;
class Room;

class Person
{
protected:
	std::string _name;
	Room* _currentRoom;
public:
	Person(const std::string& p_name);
	virtual ~Person();

	const std::string& getName();
	Room* room();
};

class Staff : public Person
{
public:
	Staff(const std::string& p_name);
	virtual void sign(Form* p_form);
};

class Student : public Person
{
private:
	std::set<Course*> _subscribedCourse;

public:
	Student(const std::string& p_name);
	void attendClass(const Classroom& p_classroom);
	void exitClass();
	void graduate(const Course& p_course);
};

class Headmaster : public Staff {
public:
	Headmaster(std::string p_name);

	void sign(Form* p_form) override;
	void receiveForm(Form* p_form);
};

class Secretary : public Staff
{
private:
	std::vector<Form*> _formsCreated;

public:
	Secretary(std::string p_name);

	Form* createForm(FormType p_formType);
	void archiveForm();
};

class Professor : public Staff
{
	private:
		Course* _currentCourse;

	public:
		Professor(std::string p_name);
		void assignCourse(Course* p_course);
		void doClass();
		void closeCourse();
};