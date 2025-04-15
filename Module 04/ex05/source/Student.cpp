#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"

void Student::requestSubscriptionToCourse(Course* p_course) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::SubscriptionToCourse);
    dynamic_cast<SubscriptionToCourseForm*>(form)->fill(this, p_course);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    Secretary::getInstance().archiveForm(form);
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
    std::cout << "[Student] " << _name << " has been graduate from course " << p_course->getName() << std::endl;
}

void Student::startPause() {
    std::cout << "[Student] " << _name << " start pause." << std::endl;
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }
    if (Courtyard* courtyard = RoomList::getInstance().getCourtyard()) {
        std::cout << "[Student] " << _name << " enter courtyard." << std::endl;
        courtyard->enter(this);
        enterRoom(courtyard);
    } else {
        std::cout << "[Student] " << _name << " no courtyard available." << std::endl;
    }
}

void Student::endPause() {
    std::cout << "[Student] " << _name << " end pause." << std::endl;
    Room* previous = _previousRoom;
    if (dynamic_cast<Courtyard*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " is exiting courtyard." << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }
    if (dynamic_cast<Classroom*>(previous)) {
        std::cout << "[Student] " << _name << " enter classroom." << std::endl;
        previous->enter(this);
        enterRoom(previous);
    } else {
        std::cout << "[Student] " << _name << " no classroom available." << std::endl;
    }
}

void Student::startLunchBreak() {
    std::cout << "[Student] " << _name << " start lunch break." << std::endl;
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }
}

void Student::endLunchBreak() {
    std::cout << "[Student] " << _name << " end lunch break." << std::endl;
    if (dynamic_cast<Classroom*>(_previousRoom)) {
        std::cout << "[Student] " << _name << " enter classroom." << std::endl;
        _previousRoom->enter(this);
        enterRoom(_previousRoom);
    } else {
        std::cout << "[Student] " << _name << " no classroom available." << std::endl;
    }
}

void Student::update(Event p_event) {
    if (p_event == Event::RingBell) {
        if (Classroom* classroom = dynamic_cast<Classroom*>(_currentRoom)) {
            startPause();
        } else {
            endPause();
        }
    }
}