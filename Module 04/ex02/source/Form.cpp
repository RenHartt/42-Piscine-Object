#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include "Person.hpp"

void CourseFinishedForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Course finished for " << _course->getName() << std::endl;
        for (auto student : _course->getStudents()) {
            student->graduate(_course);
        }
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void NeedMoreClassRoomForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Need more classroom for " << _course->getName() << std::endl;
        new Classroom(_course);
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void NeedCourseCreationForm::execute() const {
    if (isSigned() == true) {
        std::cout << "Course created: " << _courseName << std::endl;
        _professor->assignCourse(new Course(_courseName, _professor, _numberOfClassToGraduate, _maximumNumberOfStudent));
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void SubscriptionToCourseForm::execute() const {

    if (isSigned() == true) {
        std::cout << "Student " << _student->getName() << " subscribed to course " << _course->getName() << std::endl;
        _course->subscribe(_student);
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}