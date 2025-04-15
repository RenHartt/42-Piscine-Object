#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"

void Professor::requestCourseCreation(std::string p_courseName, int p_numberOfClassToGraduate, int p_maximumNumberOfStudent) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::NeedCourseCreation);
    dynamic_cast<NeedCourseCreationForm*>(form)->fill(p_courseName, this, p_numberOfClassToGraduate, p_maximumNumberOfStudent);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Professor::requestMoreClassRoom(Course* p_course) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::NeedMoreClassRoom);
    dynamic_cast<NeedMoreClassRoomForm*>(form)->fill(p_course, this);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Professor::requestCourseFinished(Student* p_student, Course* p_course) {
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    Form* form = headmaster->requestForm(FormType::CourseFinished);
    dynamic_cast<CourseFinishedForm*>(form)->fill(p_student, p_course);
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
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
    std::set<Student*> studentToGraduate;
    for (const auto& s : _currentCourse->getStudents()) {
        s->exitClass();
        if (s->getSubscribedCourses().at(_currentCourse) == 0) {
            studentToGraduate.insert(s);
        }
    }

    dynamic_cast<Classroom*>(_currentRoom)->assignCourse(nullptr);
    this->exitRoom();

    for (const auto& s : studentToGraduate) {
        requestCourseFinished(s, _currentCourse);
    }
}