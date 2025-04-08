#include "Form.hpp"
#include "Course.hpp"
#include "Person.hpp"
#include "Room.hpp"

#include <iostream>

void CourseFinishedForm::execute(Headmaster* p_headMaster) const {
    if (isSigned() == true) {
        p_headMaster->processCourseFinished(_course);
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void NeedMoreClassRoomForm::execute(Headmaster* p_headMaster) const {
    if (isSigned() == true) {
        p_headMaster->processNeedMoreClassRoom(_course);        
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void NeedCourseCreationForm::execute(Headmaster* p_headMaster) const {
    if (isSigned() == true) {
        p_headMaster->processNeedCourseCreation(_courseName, _professor, _maxStudent, _nbrGraduate);
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}

void SubscriptionToCourseForm::execute(Headmaster* p_headMaster) const {
    if (isSigned() == true) {
        p_headMaster->processSubscriptionToCourse(_student, _course);
    } else {
        std::cout << "Form is not signed." << std::endl;
    }
}