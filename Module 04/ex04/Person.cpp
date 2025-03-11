#include <memory>
#include <set>
#include <string>
#include <iostream>

#include "Person.hpp"
#include "Course.hpp"
#include "Form.hpp"

Person::Person(std::string p_name): _name(p_name), _currentRoom(nullptr) {}
std::string Person::getName() const { return _name; }
std::shared_ptr<Room> Person::room() { return (_currentRoom); }

Staff::Staff(std::string p_name): Person(p_name) {}
void Staff::sign(std::shared_ptr<Form> p_form) {
    std::cerr << _name << " is not authorized to sign forms." << std::endl;
}

Student::Student(std::string p_name): Person(p_name) {}
void Student::attendClass(std::shared_ptr<Course> p_course) {
    if (_subscribedCourse.insert(p_course).second) {
        p_course->subscribe(std::make_shared<Student>(this));
        std::cout << _name << " has enrolled in " << p_course->getName() << ".\n";
    } else {
        std::cerr << _name << " is already in " << p_course->getName() << ".\n";
    }
}
void Student::exitClass(std::shared_ptr<Course> p_course) {
    if (_subscribedCourse.erase(p_course) > 0) {
        std::cout << _name << " has dropped " << p_course->getName() << ".\n";
    } else {
        std::cerr << _name << " is not in " << p_course->getName() << ".\n";
    }
}
void Student::graduate(std::shared_ptr<Course> p_course) {
    if (_subscribedCourse.erase(p_course) > 0) {
        p_course->graduateStudent(std::make_shared<Student>(this));
    } else {
        std::cerr << _name << " is not enrolled in " << p_course->getName() << ".\n";
    }
}

Headmaster::Headmaster(std::string p_name): Staff(p_name) {}
void Headmaster::sign(std::shared_ptr<Form> p_form) {
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
void Headmaster::receiveForm(std::shared_ptr<Form> p_form) {
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
std::shared_ptr<Form> Secretary::createForm(FormType p_formType) {
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

Professor::Professor(std::string p_name): Staff(p_name) {}
void Professor::assignCourse(std::shared_ptr<Course> p_course) {
    p_course->assign(this);
}
void Professor::doClass() {

}
void Professor::closeCourse() {

}