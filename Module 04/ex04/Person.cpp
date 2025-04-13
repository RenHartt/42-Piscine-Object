#include "Person.hpp"
#include "Form.hpp"
#include "Room.hpp"
#include "Course.hpp"

void Headmaster::receiveForm(Form* p_form) {
    _formToValidate.insert(p_form);
}

void Headmaster::sign() {
    for (auto form : _formToValidate) {
        if (form->isFilled()) {
            form->sign();
            std::cout << "[Headmaster] Form signed by " << getName() << std::endl;
        } else {
            std::cout << "[Headmaster] Form is not filled." << std::endl;
        }
    }
    _formToValidate.clear();
}

void Headmaster::attendYourCourse() {
    std::cout << "[Headmaster] " << _name << " launch the classes." << std::endl;
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->ensureCourse();
        p->ensureClassroom();
    }
    for (const auto& s : StudentList::getInstance().getList()) {
        s->ensureCourse();
    }
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->doClass();
    }
}

void Headmaster::finishYourCourse() {
    std::cout << "[Headmaster] " << _name << " finish the classes." << std::endl;
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->closeCourse();
    }
}


Form* Headmaster::requestForm(FormType p_formType) {
    return StaffList::getInstance().getSecretary()->createForm(p_formType);
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

void Professor::startPause() {
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Professor] " << _name << " start pause." << std::endl;
        _previousRoom = _currentRoom;
        _currentRoom->exit(this);
        exitRoom();
    }

    StaffRestRoom* staffRestRoom = RoomList::getInstance().getStaffRestRoom();
    if (staffRestRoom != nullptr) {
        std::cout << "[Professor] " << _name << " enter staff rest room." << std::endl;
        staffRestRoom->enter(this);
        enterRoom(staffRestRoom);
    } else {
        std::cout << "[Professor] " << _name << " no staff rest room available." << std::endl;
    }
}

void Professor::endPause() {
    if (dynamic_cast<StaffRestRoom*>(_currentRoom)) {
        std::cout << "[Professor] " << _name << " end pause." << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }

    if (Classroom* classroom = dynamic_cast<Classroom*>(_previousRoom)) {
        std::cout << "[Professor] " << _name << " enter classroom." << std::endl;
        classroom->enter(this);
        enterRoom(classroom);
    } else {
        std::cout << "[Professor] " << _name << " no classroom available." << std::endl;
    }
}	

void Professor::update(Event p_event) {
    if (p_event == Event::RingBell) {
        if (Classroom* classroom = dynamic_cast<Classroom*>(_currentRoom)) {
            startPause();
        } else {
            endPause();
        }
    }
}

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

void Student::startPause() {
    if (dynamic_cast<Classroom*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " start pause." << std::endl;
        _previousRoom = _currentRoom;
        _currentRoom->exit(this);
        exitRoom();
    }

    Courtyard* courtyard = RoomList::getInstance().getCourtyard();
    if (courtyard) {
        std::cout << "[Student] " << _name << " enter courtyard." << std::endl;
        courtyard->enter(this);
        enterRoom(courtyard);
    } else {
        std::cout << "[Student] " << _name << " no courtyard available." << std::endl;
    }
}

void Student::endPause() {
    if (dynamic_cast<Courtyard*>(_currentRoom)) {
        std::cout << "[Student] " << _name << " end pause." << std::endl;
        _currentRoom->exit(this);
        exitRoom();
    }

    if (Classroom* classroom = dynamic_cast<Classroom*>(_previousRoom)) {
        std::cout << "[Student] " << _name << " enter classroom." << std::endl;
        classroom->enter(this);
        enterRoom(classroom);
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