#pragma once

#include <string>
#include <set>
#include <memory>

class Form;
class Room;
class Course;
class Classroom;
class Student;
class Professor;
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
	Staff(std::string p_name) : Person(p_name) {}
	virtual ~Staff() {}
};


class Headmaster : public Staff
{
private:
	std::set<Form*> _formToValidate;
	
public:
	Headmaster(std::string p_name) : Staff(p_name) {}
	~Headmaster() {}

	void receiveForm(Form* p_form);
	void sign(Form* p_form);
	void processCourseFinished(Course* p_course);
	void proccessNeedMoreClassRoom(Course* p_course);
	void processNeedCourseCreation(std::string p_courseName, Professor* p_professor);
	void processSubscriptionToCourse(Student* p_student, Course* p_course);
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
	
	Form* requestCourseCreationForm(std::string p_courseName, Secretary* p_secretary);
	void assignCourse(Course* p_course) { _currentCourse = p_course; }
	
	void doClass();
	void closeCourse();
};

class Student : public Person
{
private:
	std::set<Course*> _subscribedCourse;

public:
	Student(std::string p_name) : Person(p_name) {}
	~Student() {}

	Form* requestSubscriptionToCourseForm(Course* p_course, Secretary* p_secretary);
	
	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(Course* p_course);
};
