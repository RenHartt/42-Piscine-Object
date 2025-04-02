#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "List.hpp"
#include "Room.hpp"

#include <iostream>

void Headmaster::receiveForm(Form* p_form) {
    _formToValidate.insert(p_form);
}

void Headmaster::sign(Form* p_form) {
    if (p_form->isFilled()) {
        p_form->sign();
        std::cout << "Form signed by " << getName() << std::endl;
    } else {
        std::cout << "Form is not filled." << std::endl;
    }
}

void Headmaster::processCourseFinished(Course* p_course) {
    std::cout << "Course " << p_course->getName() << " has finished." << std::endl;
}

void Headmaster::proccessNeedMoreClassRoom(Course* p_course) {
    std::cout << "[Headmaster] creating new classroom for course " << p_course->getName() << "." << std::endl;
    
    Classroom* newRoom = new Classroom();
    newRoom->assignCourse(p_course);
    RoomList::getInstance().addToList(newRoom);
}

void Headmaster::processNeedCourseCreation(std::string p_courseName, Professor* p_professor) {
    std::cout << "[Headmaster] Creating course: " << p_courseName << " for professor " << p_professor->getName() << "." << std::endl;

    Course* newCourse = new Course(p_courseName);
    newCourse->assign(p_professor);
    p_professor->assignCourse(newCourse);
    CourseList::getInstance().addToList(newCourse);
}

void Headmaster::processSubscriptionToCourse(Student* p_student, Course* p_course) {
    std::cout << "[Headmaster] Subscribing student " << p_student->getName() << " to course " << p_course->getName() << "." << std::endl;
    
    p_course->subscribe(p_student);
}


Form* Secretary::createForm(FormType p_formType) {
    switch (p_formType) {
        case FormType::CourseFinished:
            return new CourseFinishedForm();
        case FormType::NeedMoreClassRoom:
            return new NeedMoreClassRoomForm();
        case FormType::NeedCourseCreation:
            return new NeedCourseCreationForm();
        case FormType::SubscriptionToCourse:
            return new SubscriptionToCourseForm();
        default:
            return nullptr;
    }
}

Form* Professor::requestCourseCreationForm(std::string p_courseName, Secretary* p_secretary) {
    std::cout << "[Professor] Requesting course creation: " << p_courseName << std::endl;
    Form* form = p_secretary->createForm(FormType::NeedCourseCreation);
    static_cast<NeedCourseCreationForm*>(form)->fill(p_courseName, this);
    return form;
}

Form* Student::requestSubscriptionToCourseForm(Course* p_course, Secretary* p_secretary) {
    std::cout << "[Student] Requesting subscription to course: " << p_course->getName() << std::endl;
    Form* form = p_secretary->createForm(FormType::SubscriptionToCourse);
    static_cast<SubscriptionToCourseForm*>(form)->fill(this, p_course);
    return form;
}