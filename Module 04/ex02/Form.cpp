#include "Form.hpp"

#include <iostream>

#include "Course.hpp"
#include "List.hpp"
#include "Room.hpp"
#include "Person.hpp"

void Form::setFilled(bool state) { _isFilled = state; }
void Form::signForm() { _signed = true; }
Form::Form(FormType p_formType) : _formType(p_formType), _signed(false), _isFilled(false) {}
Form::~Form() {}
bool Form::isSigned() const { return _signed; }
bool Form::isFilled() const { return _isFilled; }
FormType Form::getFormType() { return _formType; }

CourseFinishedForm::CourseFinishedForm() : Form(FormType::CourseFinished) {}
void CourseFinishedForm::fillForm(Course* course) {
    _course = course;
    setFilled(true);
    std::cout << "Course Finished Form filled" << std::endl;
}
void CourseFinishedForm::execute() {
    if (!_course || _course == nullptr) {
        std::cout << "No course to finish." << std::endl;
    } else if (isSigned() == false) {
        std::cout << "Cannot execute a non-signed form." << std::endl;
    } else {
        std::cout << "Processing Course Finished Form" << std::endl;
        CourseList::getInstance().removeFromList(_course);
        delete _course;
    }
}
 
NeedMoreClassRoomForm::NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
void NeedMoreClassRoomForm::fillForm() {
    setFilled(true);
    std::cout << "Need More Classroom Form filled." << std::endl;
}
void NeedMoreClassRoomForm::execute() {
    if (isSigned() == false) {
        std::cout << "Cannot execute a non-signed form." << std::endl;
    } else {
        std::cout << "Processing Need More Class Room Form." << std::endl;
        RoomList::getInstance().addToList(new Classroom());
    }
}
   
NeedCourseCreationForm::NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
void NeedCourseCreationForm::fillForm(const std::string& courseName) {
    _courseName = courseName;
    setFilled(true);
    std::cout << "Need Course Creation Form filled. Course: " << _courseName << std::endl;
}
void NeedCourseCreationForm::execute() {
    if (isSigned() == false) {
        std::cout << "Cannot execute a non-signed form." << std::endl;
    } else {
        std::cout << "Processing Need Course Creation Form." << std::endl;
        CourseList::getInstance().addToList(new Course(_courseName));
    }
}
 
SubscriptionToCourseForm::SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
void SubscriptionToCourseForm::fillForm(Student* student, Course* course) {
    _student = student;
    _course = course;
    setFilled(true);
    std::cout << "Subscription to Course Form filled."
                << " Student: " << _student->getName() 
                << ", Course: " << _course->getName() << std::endl;
}
void SubscriptionToCourseForm::execute() {
    if (CourseList::getInstance().getFromList(_course->getName()) == nullptr) {
        std::cout << "No course to subscribe." << std::endl;
    } else if (StudentList::getInstance().getFromList(_student->getName()) == nullptr) {
        std::cout << "No student to add to course." << std::endl;
    } else if (isSigned() == false) {
        std::cout << "Cannot execute a non-signed form." << std::endl;
    } else {
        std::cout << "Processing Subscription To Course Form." << std::endl;
        _course->subscribe(_student);
    }
}