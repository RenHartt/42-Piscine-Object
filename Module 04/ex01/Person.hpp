#pragma once

#include <string>
#include <memory>
#include <set>

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
		std::shared_ptr<Room> _currentRoom;
	public:
		Person(std::string p_name): _name(p_name) {}
		virtual ~Person() {}

		std::shared_ptr<Room> room() {
			return (_currentRoom);
		}
};

class Staff : public Person
{
	public:
		Staff(std::string p_name): Person(p_name) {}
		void sign(std::shared_ptr<Form> p_form);
};

class Student : public Person
{
	private:
		std::set<std::shared_ptr<Course>> _subscribedCourse;

	public:
		Student(std::string p_name): Person(p_name) {}
		void attendClass(std::shared_ptr<Classroom> p_classroom);
		void exitClass();
		void graduate(std::shared_ptr<Course> p_course);
};

class Headmaster : public Staff
{
	private:
		std::set<std::shared_ptr<Form>> _formToValidate;
		
	public:
		Headmaster(std::string p_name): Staff(p_name) {}
		void receiveForm(std::shared_ptr<Form> p_form);
};

class Secretary : public Staff
{
	public:
		Secretary(std::string p_name): Staff(p_name) {}
		std::shared_ptr<Form> createForm(FormType p_formType);
		void archiveForm();
};

class Professor : public Staff
{
	private:
		std::shared_ptr<Course> _currentCourse;

	public:
		Professor(std::string p_name): Staff(p_name) {}
		void assignCourse(std::shared_ptr<Course> p_course);
		void doClass();
		void closeCourse();
};
