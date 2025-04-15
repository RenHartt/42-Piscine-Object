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
    _subscribedCourse[p_classroom->getCurrentCourse()]--;
}

void Student::exitClass() {
    if (_currentRoom != nullptr) {
        std::cout << "[Student] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        this->exitRoom();
    }
}

void Student::graduate(Course* p_course) {
    std::cout << "[Student] " << _name << " graduated from course " << p_course->getName() << std::endl;
}

void Student::startPause() {
    std::cout << "[Student] " << _name << " start pause." << std::endl;
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        exitRoom();
    }
    if (Courtyard* courtyard = RoomList::getInstance().getCourtyard()) {
        std::cout << "[Student] " << _name << " enter courtyard." << std::endl;
        enterRoom(courtyard);
    } else {
        std::cout << "[Student] " << _name << " no courtyard available." << std::endl;
    }
}

void Student::endPause() {
    std::cout << "[Student] " << _name << " end pause." << std::endl;
    Room* nextRoom = _previousRoom;
    if (dynamic_cast<Courtyard*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " is exiting courtyard." << std::endl;
        exitRoom();
    }
    if (dynamic_cast<Classroom*>(nextRoom)) {
        std::cout << "[Student] " << _name << " enter classroom." << std::endl;
        enterRoom(nextRoom);
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