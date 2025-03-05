#pragma once

#include <string>
#include <memory>
#include <set>
#include <vector>
#include <iostream>

class Person
{
	protected:
		std::string _name;
		std::shared_ptr<Room> _currentRoom;
	public:
		Person(std::string p_name): _name(p_name), _currentRoom(nullptr) {}
		virtual ~Person() {}

		std::string getName() const { return _name; }

		std::shared_ptr<Room> room() { return (_currentRoom); }
};

class Staff : public Person
{
	public:
		Staff(std::string p_name): Person(p_name) {}
		virtual void sign(std::shared_ptr<Form> p_form) {
			std::cerr << _name << " is not authorized to sign forms." << std::endl;
		}
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

class Headmaster : public Staff {
    public:
        Headmaster(std::string p_name): Staff(p_name) {}

        void sign(std::shared_ptr<Form> p_form) override {
            if (!p_form) {
                std::cerr << "Error: Cannot sign a null form!" << std::endl;
                return;
            }
            if (p_form->isFilled()) {
                p_form->signForm();
                std::cout << "Form signed by " << _name << "." << std::endl;
            } else {
                std::cerr << "Error: Form is not filled, cannot be signed!" << std::endl;
            }
        }

        void receiveForm(std::shared_ptr<Form> p_form) {
            if (!p_form) {
                std::cerr << "Error: Received a null form!" << std::endl;
                return;
            }
            std::cout << "Headmaster received a form of type: " 
                      << static_cast<int>(p_form->getFormType()) << std::endl;
            sign(p_form);
            p_form->execute();
        }
};

class Secretary : public Staff
{
	private:
		std::vector<std::shared_ptr<Form>> _formsCreated;

	public:
		Secretary(std::string p_name): Staff(p_name) {}

		std::shared_ptr<Form> createForm(FormType p_formType) {
			switch (p_formType) {
				case FormType::CourseFinished:
					std::cout << "Form Course finished created." << std::endl;
					return std::make_shared<CourseFinishedForm>();
				case FormType::NeedMoreClassRoom:
					std::cout << "Form Need More ClassRoom created." << std::endl;
					return std::make_shared<NeedMoreClassRoomForm>();
				case FormType::NeedCourseCreation:
					std::cout << "Form Need Course created." << std::endl;
					return std::make_shared<NeedCourseCreationForm>();
				case FormType::SubscriptionToCourse:
					std::cout << "Form SUbscription To Course created." << std::endl;
					return std::make_shared<SubscriptionToCourseForm>();
				default:
					std::cout << "Error: Unknown Form." << std::endl;
					return nullptr;
			}
		}
		
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