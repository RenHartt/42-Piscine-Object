#include "Form.hpp"
#include "Course.hpp"
#include "Person.hpp"
#include "Room.hpp"

#include <iostream>

void CourseFinishedForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Course " << _course->getName() << " has finished." << std::endl;
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void NeedMoreClassRoomForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Need more class room for course " << _course->getName() << "." << std::endl;
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void NeedCourseCreationForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Need course creation for course " << _courseName << " with professor " << _professor->getName() << "." << std::endl;
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void SubscriptionToCourseForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Student " << _student->getName() << " has subscribed to course " << _course->getName() << "." << std::endl;
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}