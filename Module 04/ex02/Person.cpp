#include "Person.hpp"

#include <string>
#include <memory>
#include <set>
#include <vector>
#include <iostream>

#include "Form.hpp"
#include "Room.hpp"

Person::Person(const std::string& p_name): _name(p_name), _currentRoom(nullptr) {}
Person::~Person() {}
const std::string& Person::getName() { return _name; }
Room* Person::room() { return (_currentRoom); }

Staff::Staff(const std::string& p_name): Person(p_name) {}
void Staff::sign(Form* p_form) { std::cerr << _name << " is not authorized to sign forms." << std::endl; }

Student::Student(const std::string& p_name): Person(p_name) {}
void Student::attendClass(const Classroom& p_classroom) {}
void Student::exitClass() {}
void Student::graduate(const Course& p_course) {}

Headmaster::Headmaster(std::string p_name): Staff(p_name) {}
void Headmaster::sign(Form* p_form) {
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
void Headmaster::receiveForm(Form* p_form) {
    if (!p_form) {
        std::cerr << "Error: Received a null form!" << std::endl;
        return;
    }
    std::cout << "Headmaster received a form of type: " 
              << static_cast<int>(p_form->getFormType()) << std::endl;
    sign(p_form);
    p_form->execute();
}

Secretary::Secretary(std::string p_name): Staff(p_name) {}
Form* Secretary::createForm(FormType p_formType) {
	switch (p_formType) {
		case FormType::CourseFinished:
			std::cout << "Form Course finished created." << std::endl;
			return new CourseFinishedForm;
		case FormType::NeedMoreClassRoom:
			std::cout << "Form Need More ClassRoom created." << std::endl;
			return new NeedMoreClassRoomForm;
		case FormType::NeedCourseCreation:
			std::cout << "Form Need Course created." << std::endl;
			return new NeedCourseCreationForm;
		case FormType::SubscriptionToCourse:
			std::cout << "Form SUbscription To Course created." << std::endl;
			return new SubscriptionToCourseForm;
		default:
			std::cout << "Error: Unknown Form." << std::endl;
			return nullptr;
	}
}
void Secretary::archiveForm() {}

Professor::Professor(std::string p_name): Staff(p_name) {}
void Professor::assignCourse(Course* p_course) {}
void Professor::doClass() {}
void Professor::closeCourse() {}