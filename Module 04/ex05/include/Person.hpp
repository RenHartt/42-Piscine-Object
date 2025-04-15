#pragma once

#include <string>
#include <set>
#include <map>
#include <memory>

#include "List.hpp"
#include "Event.hpp"
#include "Observer.hpp"
#include "Room.hpp"

enum class FormType;
class Form;
class Classroom;

class Person
{
protected:
	std::string _name;
	Room* _currentRoom = nullptr;
	Room* _previousRoom = nullptr;
public:
	Person(std::string p_name) : _name(p_name) {}
	virtual ~Person() {}

	const std::string& getName() const { return _name; }
	Room* room() { return _currentRoom; }

	void enterRoom(Room* p_room) {
		_currentRoom = p_room;
		_currentRoom->enter(this);
	}
	
	void exitRoom() {
		_previousRoom = _currentRoom;
		if (_currentRoom != nullptr) {
			_currentRoom->exit(this);
		}
		_currentRoom = nullptr;
	}
};

class Staff : public Person
{
public:
	Staff(std::string p_name) : Person(p_name) {
		StaffList::getInstance().addToList(this);
	}
	virtual ~Staff() {}
};

class Headmaster : public Staff, public Subject, public Singleton<Headmaster>
{
private:
	std::set<Form*> _formToValidate;
	std::set<std::pair<Student*, Course*>> _studentsToGraduate;
	std::set<Observer*> _observers;

	Headmaster(std::string p_name = "Headmaster") : Staff(p_name) {}
public:
	friend class Singleton<Headmaster>;
	
	void attendYourCourse();
	void finishYourCourse();

	void addStudentToGraduate(Student* p_student, Course* p_course) {
		_studentsToGraduate.insert(std::make_pair(p_student, p_course));
	}
	void graduateStudents();
	std::set<std::pair<Student*, Course*>> getStudentsToGraduate() const { return _studentsToGraduate; }
	
	Form* requestForm(FormType p_formType);
	void receiveForm(Form* p_form);
	void sign();

	void attach(Observer* p_observer) override { _observers.insert(p_observer); }
	void detach(Observer* p_observer) override { _observers.erase(p_observer); }
	void notify(Event p_event) override {
		std::cout << "[Headmaster] 🔔 ring the bell. 🔔" << std::endl;
		for (auto observer : _observers) {
			observer->update(p_event);
		}
	}
};

class Secretary : public Staff, public Singleton<Secretary>
{
private:
	Secretary(std::string p_name = "Secretary") : Staff(p_name) {}
public:
	friend class Singleton<Secretary>;

	Form* createForm(FormType p_formType);
	void archiveForm(Form* p_form) {
		std::cout << "[Secretary] Archive form." << std::endl;
		SecretarialOffice::getInstance().archiveForm(p_form);
	}
};

class Student : public Person, public Observer
{
private:
	std::map<Course*, int> _subscribedCourse;

	void requestSubscriptionToCourse(Course* p_course);
public:
	Student(std::string p_name) : Person(p_name) {
		StudentList::getInstance().addToList(this);
	}

	const std::map<Course*, int>& getSubscribedCourses() const { return _subscribedCourse; }

	void subscribe(Course* p_course);
	void unsubscribe(Course* p_course);
	void ensureCourse();
	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(Course* p_course);

	void startPause();
	void endPause();
	void startLunchBreak();
	void endLunchBreak();
	void update(Event p_event) override;
};

class Professor : public Staff, public Observer
{
private:
	Course* _currentCourse = nullptr;

	void requestCourseCreation(std::string p_courseName, int p_numberOfClassToGraduate, int p_maximumNumberOfStudent);
	void requestMoreClassRoom(Course* p_course);
	void requestCourseFinished(Student* p_student, Course* p_course);
public:
	Professor(std::string p_name) : Staff(p_name) {}

	Course* getCourse() const { return _currentCourse; }
	void assignCourse(Course* p_course) { _currentCourse = p_course; }

	void ensureCourse();
	void ensureClassroom();
	void doClass();
	void closeCourse();

	void startPause();
	void endPause();
	void startLunchBreak();
	void endLunchBreak();
	void update(Event p_event) override;
};