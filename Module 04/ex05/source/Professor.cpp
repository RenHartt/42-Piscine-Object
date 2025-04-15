#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"

void Professor::requestCourseCreation(std::string p_courseName, int p_numberOfClassToGraduate, int p_maximumNumberOfStudent) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::NeedCourseCreation);
    dynamic_cast<NeedCourseCreationForm*>(form)->fill(p_courseName, this, p_numberOfClassToGraduate, p_maximumNumberOfStudent);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    Secretary::getInstance().archiveForm(form);
}

void Professor::requestMoreClassRoom(Course* p_course) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::NeedMoreClassRoom);
    dynamic_cast<NeedMoreClassRoomForm*>(form)->fill(p_course, this);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    Secretary::getInstance().archiveForm(form);
}

void Professor::requestCourseFinished(Student* p_student, Course* p_course) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::CourseFinished);
    dynamic_cast<CourseFinishedForm*>(form)->fill(p_student, p_course);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    Secretary::getInstance().archiveForm(form);
}

void Professor::ensureCourse() {
    std::cout << "[Professor] " << _name << " is ensuring course." << std::endl;
    if (_currentCourse != nullptr) {
        std::cout << "[Professor] " << _name << " is already assigned to a course." << std::endl;
        return;
    }

    std::cout << "[Professor] " << _name << " check for course without professor." << std::endl;
    for (const auto& course : CourseList::getInstance().getList()) {
        if (course->getProfessor() == nullptr) {
            std::cout << "[Professor] " << _name << " assign course " << course->getName() << std::endl;
            assignCourse(course);
            course->assign(this);
            return;
        }
    }

    std::cout << "[Professor] " << _name << " No available courses to assign, request a new course." << std::endl;
    requestCourseCreation(this->_name + "_course", 5, 25);
}

void Professor::ensureClassroom() {
    std::cout << "[Professor] " << _name << " is ensuring classroom." << std::endl;
    if (_currentRoom != nullptr) {
        std::cout << "[Professor] " << _name << " is already assigned to a classroom." << std::endl;
        return;
    }

    std::cout << "[Professor] " << _name << " check for empty classroom." << std::endl;
    for (const auto& room : RoomList::getInstance().getList()) {
        if (Classroom* classroom = dynamic_cast<Classroom*>(room)) {
            if (classroom->getCurrentCourse() == nullptr) {
                std::cout << "[Professor] " << _name << " assign classroom " << room->getID() << std::endl;
                enterRoom(classroom);
                classroom->assignCourse(_currentCourse);
                return;
            }
        }
    }

    std::cout << "[Professor] " << _name << " No available classrooms to assign, request a new classroom." << std::endl;
    requestMoreClassRoom(_currentCourse);
}

void Professor::doClass() {
    std::cout << "[Professor] " << _name << " is doing class" << std::endl;
    for (const auto& s : _currentCourse->getStudents()) {
        s->attendClass(dynamic_cast<Classroom*>(_currentRoom));
    }
}

void Professor::closeCourse() {
    std::cout << "[Professor] " << _name << " is finishing class" << std::endl;
    for (const auto& s : _currentCourse->getStudents()) {
        s->exitClass();
        if (s->getSubscribedCourses().at(_currentCourse) == 0) {
            Headmaster::getInstance().addStudentToGraduate(s, _currentCourse);
        }
    }

    if (Classroom* classroom =  dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Professor] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        classroom->assignCourse(nullptr);
        classroom->exit(this);
        exitRoom();
    } else if (Classroom* classroom = dynamic_cast<Classroom*>(_previousRoom)) {
        std::cout << "[Professor] " << _name << " is exiting class " << _previousRoom->getID() << std::endl;
        classroom->assignCourse(nullptr);
        exitRoom();
    }
}

void Professor::startPause() {
    std::cout << "[Professor] " << _name << " start pause." << std::endl;
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Professor] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }
    if (StaffRestRoom* restroom = RoomList::getInstance().getStaffRestRoom()) {
        std::cout << "[Professor] " << _name << " enter staff rest room." << std::endl;
        restroom->enter(this);
        enterRoom(restroom);
    } else {
        std::cout << "[Professor] " << _name << " no staff rest room available." << std::endl;
    }
}

void Professor::endPause() {
    std::cout << "[Professor] " << _name << " end pause." << std::endl;
    Room* previous = _previousRoom;
    if (dynamic_cast<StaffRestRoom*>(_currentRoom)) {
        std::cout << "[Professor] " << _name << " is exiting staff rest room." << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }
    if (dynamic_cast<Classroom*>(previous)) {
        std::cout << "[Professor] " << _name << " enter classroom." << std::endl;
        previous->enter(this);
        enterRoom(previous);
    } else {
        std::cout << "[Professor] " << _name << " no classroom available." << std::endl;
    }
}

void Professor::startLunchBreak() {
    std::cout << "[Professor] " << _name << " start lunch break." << std::endl;
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Professor] " << _name << " is exiting class " << _currentRoom->getID() << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }
}

void Professor::endLunchBreak() {
    std::cout << "[Professor] " << _name << " end lunch break." << std::endl;
    if (dynamic_cast<Classroom*>(_previousRoom)) {
        std::cout << "[Professor] " << _name << " enter classroom." << std::endl;
        _previousRoom->enter(this);
        enterRoom(_previousRoom);
    } else {
        std::cout << "[Professor] " << _name << " no classroom available." << std::endl;
    }
}

void Professor::update(Event p_event) {
    if (p_event == Event::RingBell) {
        if (dynamic_cast<Classroom*>(_currentRoom)) {
            startPause();
        } else {
            endPause();
        }
    } else if (p_event == Event::LunchBreak) {
        if (dynamic_cast<Classroom*>(_currentRoom)) {
            startLunchBreak();
        } else {
            endLunchBreak();
        }
    }
}