#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include "Person.hpp"

void CourseFinishedForm::execute() const {
    if (isSigned() == true) {
        std::cout << "[Headmaster] evaluate student " << _student->getName() << " for course " << _course->getName() << std::endl;
        _student->graduate(_course);
        _student->unsubscribe(_course);
        _course->unsubscribe(_student);
    } else {
        std::cout << "[Headmaster] Form is not signed." << std::endl;
    }
}

void NeedMoreClassRoomForm::execute() const {
    if (isSigned() == true) {
        std::cout << "[Headmaster] create classroom for " << _professor->getName() << " for course " << _course->getName() << std::endl;
        Classroom* classroom = new Classroom(_course);
        classroom->assignCourse(_course);
        _professor->enterRoom(classroom);
    } else {
        std::cout << "[Headmaster] Form is not signed." << std::endl;
    }
}

void NeedCourseCreationForm::execute() const {
    if (isSigned() == true) {
        std::cout << "[Headmaster] create course " << _courseName << " for " << _professor->getName() << std::endl;
        _professor->assignCourse(new Course(_courseName, _professor, _numberOfClassToGraduate, _maximumNumberOfStudent));
    } else {
        std::cout << "[Headmaster] Form is not signed." << std::endl;
    }
}

void SubscriptionToCourseForm::execute() const {

    if (isSigned() == true) {
        std::cout << "[Headmaster] subscribe " << _student->getName() << " to course " << _course->getName() << std::endl;
        _student->subscribe(_course);
        _course->subscribe(_student);
    } else {
        std::cout << "[Headmaster] Form is not signed." << std::endl;
    }
}