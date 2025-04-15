#pragma once

#include <string>
#include <set>
#include <memory>

#include "List.hpp"
#include "Form.hpp"
#include "Room.hpp"

class Person
{
protected:
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
protected:

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

	void attendClass(Classroom* p_classroom) { this->_currentRoom = p_classroom; }
	void exitClass() { this->_currentRoom = nullptr; }
	void graduate(Course*) {
		std::cout << "Student " << _name << " graduated" << std::endl;
	}
};

class Headmaster : public Staff, public Singleton<Headmaster>
{
private:
	std::set<Form*> _formToValidate;
	
	Headmaster(std::string p_name = "Headmaster") : Staff(p_name) {}
public:
	friend class Singleton<Headmaster>;

	void receiveForm(Form* p_form) { _formToValidate.insert(p_form); }
	void sign() {
		for (auto form : _formToValidate) {
			if (form->isFilled()) {
				form->sign();
				std::cout << "Form signed by " << getName() << std::endl;
			} else {
				std::cout << "Form is not filled." << std::endl;
			}
		}
		_formToValidate.clear();
	}
};

class Secretary : public Staff, public Singleton<Secretary>
{
private:
	Secretary(std::string p_name = "Secretary") : Staff(p_name) {}
public:
	friend class Singleton<Secretary>;

	Form* createForm(FormType p_formType) {
		switch (p_formType) {
			case FormType::CourseFinished:
				return new CourseFinishedForm();
			case FormType::NeedMoreClassRoom:
				return new NeedMoreClassRoomForm();
			case FormType::NeedCourseCreation:
				return new NeedCourseCreationForm();
			case FormType::SubscriptionToCourse:
				return new SubscriptionToCourseForm();
			default:
				return nullptr;
		}
	}
	void archiveForm();
};

class Professor : public Staff
{
private:
	Course* _currentCourse = nullptr;

public:
	Professor(std::string p_name) : Staff(p_name) {}
	~Professor() {}

	void assignCourse(Course* p_course) { _currentCourse = p_course; }
	void doClass();
	void closeCourse();
};
