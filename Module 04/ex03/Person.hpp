#pragma once

#include <string>
#include <memory>
#include <set>
#include <vector>

class Room;
class Form;
class Classroom;
class Course;
enum class FormType;

class Person
{
	protected:
		std::string _name;
		std::shared_ptr<Room> _currentRoom;
	public:
		Person(std::string p_name);
		virtual ~Person() {}

		std::string getName() const;
		std::shared_ptr<Room> room();
};

class Staff : public Person
{
	public:
		Staff(std::string p_name);
		virtual void sign(std::shared_ptr<Form> p_form);
};

class Student : public Person
{
	private:
		std::set<std::shared_ptr<Course>> _subscribedCourse;

	public:
		Student(std::string p_name);
		void attendClass(std::shared_ptr<Classroom> p_classroom);
		void exitClass();
		void graduate(std::shared_ptr<Course> p_course);
};

class Headmaster : public Staff {
    public:
        Headmaster(std::string p_name);

        void sign(std::shared_ptr<Form> p_form) override;
        void receiveForm(std::shared_ptr<Form> p_form);
};

class Secretary : public Staff
{
	private:
		std::vector<std::shared_ptr<Form>> _formsCreated;

	public:
		Secretary(std::string p_name);

		std::shared_ptr<Form> createForm(FormType p_formType);
		void archiveForm();
};

class Professor : public Staff
{
	private:
		std::shared_ptr<Course> _currentCourse;

	public:
		Professor(std::string p_name);
		void assignCourse(std::shared_ptr<Course> p_course);
		void doClass();
		void closeCourse();
};