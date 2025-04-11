#pragma once

#include <string>
#include <set>
#include <map>
#include <memory>

#include "List.hpp"

enum class FormType;
class Form;
class Classroom;

class Person
{
protected:
	std::string _name;
	Room* _currentRoom = nullptr;
public:
	Person(std::string p_name) : _name(p_name) {}
	virtual ~Person() {}

	const std::string& getName() const { return _name; }
	void enterRoom(Room* p_room) { _currentRoom = p_room; }
	void exitRoom() { _currentRoom = nullptr; }
	Room* room() { return _currentRoom; }
};

class Staff : public Person
{
protected:

public:
	Staff(std::string p_name) : Person(p_name) {
		StaffList::getInstance().addToList(this);
	}
	virtual ~Staff() {}
};

class Headmaster : public Staff
{
private:
	std::set<Form*> _formToValidate;

public:
	Headmaster(std::string p_name) : Staff(p_name) {}
	~Headmaster() {}

	void receiveForm(Form* p_form) {
		_formToValidate.insert(p_form);
	}
	
	void sign();
	void attendYourCourse();
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

	Course* getCourse() const { return _currentCourse; }
	void assignCourse(Course* p_course) { _currentCourse = p_course; }

	void requestCourseCreation(std::string p_courseName, int p_numberOfClassToGraduate, int p_maximumNumberOfStudent);
	void requestMoreClassRoom(Course* p_course);
	void requestCourseFinished(Student* p_student, Course* p_course);

	void ensureCourse();
	void ensureClassroom();
	
	void doClass();
	void closeCourse();
};

class Student : public Person
{
private:
	std::map<Course*, int> _subscribedCourse;

	void requestSubscriptionToCourse(Course* p_course);

public:
	Student(std::string p_name) : Person(p_name) {
		StudentList::getInstance().addToList(this);
	}
	~Student() {}

	const std::map<Course*, int>& getSubscribedCourses() const { return _subscribedCourse; }

	void subscribe(Course* p_course);
	void unsubscribe(Course* p_course);
	void ensureCourse();
	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(Course* p_course);
};