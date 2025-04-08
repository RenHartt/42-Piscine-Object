#pragma once

#include <string>
#include <set>
#include <map>
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
protected:
	std::string _name;
	Room* _currentRoom = nullptr;
public:
	Person(std::string p_name) : _name(p_name) {}
	virtual ~Person() {}

	const std::string& getName() const { return _name; }
	Room* room() { return _currentRoom; }
	void exitRoom() { _currentRoom = nullptr; }
	void enterRoom(Room* p_room) { _currentRoom = p_room; }
};

class Staff : public Person
{
protected:

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
	void processNeedMoreClassRoom(Course* p_course);
	void processNeedCourseCreation(std::string p_courseName, Professor* p_professor, int p_maxStudent, int p_nbrGraduate);
	void processSubscriptionToCourse(Student* p_student, Course* p_course);

	void requireProfessorToDoClass(Professor* p_professor);
	
	void ensureProfessorHasCourse(Professor* p_professor);
	void ensureProfessorHasRoom(Professor* p_professor);
	void ensureStudentHasCourse(Student* p_student);
	void ensureAllStudentsHasCourse();
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
	
	Course* course() { return _currentCourse; }
	void assignCourse(Course* p_course) { _currentCourse = p_course; }

	Form* requestCourseCreationForm(Secretary* p_secretary, std::string p_courseName, int p_maxStudent, int p_nbrGraduate);
	
	void doClass();
	void closeCourse();
};

class Student : public Person
{
private:
	std::map<Course*, int> _subscribedCourse;

public:
	Student(std::string p_name) : Person(p_name) {}
	~Student() {}

	Form* requestSubscriptionToCourseForm(Course* p_course, Secretary* p_secretary);
	
	void subscribeToCourse(Course* p_course);
	void unsubscribeToCourse(Course* p_course);
	std::map<Course*, int>& getSubscribedCourses();

	void attendClass(Classroom* p_classroom);
	void exitClass();
	void graduate(Course* p_course);
};
