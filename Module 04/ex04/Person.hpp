#pragma once

#include <string>
#include <set>
#include <map>
#include <memory>

#include "List.hpp"

class Form;
class Room;
class Course;
class Classroom;
class Student;
class Professor;
class Headmaster;
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

	void exitRoom();
	void enterRoom(Room* p_room);

	Headmaster* callHeadmaster();
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

	void receiveForm(Form* p_form);
	void sign(Form* p_form);

	void assignProfessorToCourse(Professor* p_professor, Course* p_course);
	void assignStudentToCourse(Student* p_student, Course* p_course);
	void assignClassroomToCourse(Classroom* p_classroom, Course* p_course);
	void assignClassroomToProfessor(Classroom* p_classroom, Professor* p_professor);
	void assignClassroomToStudent(Classroom* p_classroom, Student* p_student);

	void unassignProfessorFromCourse(Professor* p_professor, Course* p_course);
	void unassignStudentFromCourse(Student* p_student, Course* p_course);
	void unassignCourseFromClassroom(Classroom* p_classroom, Course* p_course);

	void processCourseFinished(Course* p_course);
	void processNeedMoreClassRoom(Course* p_course);
	void processNeedCourseCreation(std::string p_courseName, Professor* p_professor, int p_maxStudent, int p_requiredClassesToGraduate);
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
	void removeCourse() { _currentCourse = nullptr; }
	
	Form* requestCourseCreationForm(Secretary* p_secretary, std::string p_courseName, int p_maxStudent, int p_nrequiredClassesToGraduate);
	
	void doClass();
	void closeCourse();
};

class Student : public Person
{
private:
	std::map<Course*, int> _subscribedCourse;

public:
	Student(std::string p_name) : Person(p_name) {
		StudentList::getInstance().addToList(this);
	}
	~Student() {}

	Form* requestSubscriptionToCourseForm(Course* p_course, Secretary* p_secretary);
	
	void subscribeToCourse(Course* p_course);
	void unsubscribeToCourse(Course* p_course);
	bool isSubscribedToCourse(Course* p_course) const;
	std::map<Course*, int>& getSubscribedCourses();

	void attendClass(Classroom* p_classroom);
	void attendCourse(Course* p_course);
	void exitClass();
	void graduate(Course* p_course);
};
