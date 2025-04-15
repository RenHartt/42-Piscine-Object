#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"

void Student::requestSubscriptionToCourse(Course* p_course) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::SubscriptionToCourse);
    dynamic_cast<SubscriptionToCourseForm*>(form)->fill(this, p_course);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Student::subscribe(Course* p_course) {
    if (_subscribedCourse.count(p_course) == 0) {
        std::cout << "[Student] " << _name << " subscribed to course " << p_course->getName() << std::endl;
        _subscribedCourse[p_course] = p_course->getNumberOfClassToGraduate();
    } else {
        std::cout << "[Student] " << _name << " Already subscribed to course " << p_course->getName() << std::endl;
    }
}

void Student::unsubscribe(Course* p_course) {
    if (_subscribedCourse.erase(p_course)) {
        std::cout << "[Student] " << _name << " unsubscribed from course " << p_course->getName() << std::endl;
    } else {
        std::cout << "[Student] " << _name << " Not subscribed to course " << p_course->getName() << std::endl;
    }
}

void Student::ensureCourse() {
    std::cout << "[Student] " << _name << " is ensuring course subscription." << std::endl;
    if (_subscribedCourse.empty()) {
        for (const auto& course : CourseList::getInstance().getList()) {
            if (course->getStudents().size() < course->getMaximumNumberOfStudent()) {
                requestSubscriptionToCourse(course);
                return;
            }
        }
        std::cout << "[Student] " << _name << " No available courses to subscribe." << std::endl;
    } 
}

void Student::attendClass(Classroom* p_classroom) { 
    std::cout << "[Student] " << _name << " is attending class " << p_classroom->getCurrentCourse()->getName() << std::endl;
    this->enterRoom(p_classroom);
    p_classroom->enter(this);
    _subscribedCourse[p_classroom->getCurrentCourse()]--;
}

void Student::exitClass() {
    if (_currentRoom != nullptr) {
        std::cout << "[Student] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        _currentRoom->exit(this);
        this->exitRoom();
    }
}

void Student::graduate(Course* p_course) {
    std::cout << "[Student] " << _name << " graduated from course " << p_course->getName() << std::endl;
}