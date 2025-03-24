#include "Person.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Course.hpp"
#include "Room.hpp"

#include <string>
#include <set>
#include <vector>
#include <iostream>

Person::Person(std::string p_name): _name(p_name), _currentRoom(nullptr) {}
std::string Person::getName() const { return _name; }
std::shared_ptr<Room> Person::room() { return (_currentRoom); }

Staff::Staff(std::string p_name): Person(p_name) {}
void Staff::sign(std::shared_ptr<Form> p_form) {
    std::cerr << _name << " is not authorized to sign forms." << std::endl;
}

Student::Student(std::string p_name): Person(p_name) {}
void Student::attendClass(std::shared_ptr<Course> p_course) {

}
void Student::exitClass(std::shared_ptr<Course> p_course) {

}
void Student::graduate(std::shared_ptr<Course> p_course) {

}

Headmaster::Headmaster(std::string p_name): Staff(p_name) {}
std::shared_ptr<Secretary> Headmaster::getSecretary() {
    auto staffList = StaffList::getInstance().getList();
    for (const auto& staff : staffList) {
        auto secretary = std::dynamic_pointer_cast<Secretary>(staff);
        if (secretary) {
            return secretary;
        }
    }
    return nullptr;
}
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
void Headmaster::createCourse(std::shared_ptr<Professor> professor, const std::string& courseName) {
    auto secretary = getSecretary();
    if (!secretary) {
        std::cerr << "Error: No secretary found." << std::endl;
        return;
    }
    auto form = secretary->createForm(FormType::NeedCourseCreation);
    if (!form) {
        std::cerr << "Error: Could not create form." << std::endl;
        return;
    }
    auto needCourseCreationForm = std::static_pointer_cast<NeedCourseCreationForm>(form);
    needCourseCreationForm->fillForm(std::make_shared<Course>(courseName), professor);
    receiveForm(form);
}
void Headmaster::subscribeStudent(std::shared_ptr<Student> student, const std::string& courseName) {
    auto secretary = getSecretary();
    if (!secretary) {
        std::cerr << "Error: No secretary found." << std::endl;
        return;
    }
    auto form = secretary->createForm(FormType::SubscriptionToCourse);
    if (!form) {
        std::cerr << "Error: Could not create form." << std::endl;
        return;
    }
    auto subscriptionToCourseForm = std::static_pointer_cast<SubscriptionToCourseForm>(form);
    auto courseList = CourseList::getInstance().getList();
    for (const auto& course : courseList) {
        if (course->getName() == courseName) {
            subscriptionToCourseForm->fillForm(student, course);
            receiveForm(subscriptionToCourseForm);
            return;
        }
    }
    std::cerr << "Error: Course not found." << std::endl;
}
void Headmaster::graduateStudent(std::shared_ptr<Student> student, const std::string& courseName) {
    auto secretary = getSecretary();
    if (!secretary) {
        std::cerr << "Error: No secretary found." << std::endl;
        return;
    }
    auto form = secretary->createForm(FormType::CourseFinished);
    if (!form) {
        std::cerr << "Error: Could not create form." << std::endl;
        return;
    }
    auto courseFinishedForm = std::static_pointer_cast<CourseFinishedForm>(form);
    auto courseList = CourseList::getInstance().getList();
    for (const auto& course : courseList) {
        if (course->getName() == courseName) {
            courseFinishedForm->fillForm(student, course);
            receiveForm(form);
            return;
        }
    }
    std::cerr << "Error: Course not found." << std::endl;
}
void Headmaster::requestClassroom(int roomCount, const std::string& reason) {
    auto secretary = getSecretary();
    if (!secretary) {
        std::cerr << "Error: No secretary found." << std::endl;
        return;
    }
    auto form = secretary->createForm(FormType::NeedMoreClassRoom);
    if (!form) {
        std::cerr << "Error: Could not create form." << std::endl;
        return;
    }
    auto needMoreClassRoomForm = std::static_pointer_cast<NeedMoreClassRoomForm>(form);
    needMoreClassRoomForm->fillForm(roomCount, reason);
    receiveForm(form);
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
    
}
void Professor::doClass() {
    
}
void Professor::closeCourse() {
    
}