#include "Person.hpp"
#include "Form.hpp"
#include "Room.hpp"
#include "Course.hpp"

void Headmaster::sign() {
    for (auto form : _formToValidate) {
        if (form->isFilled()) {
            form->sign();
            std::cout << "Form signed by " << getName() << std::endl;
        } else {
            std::cout << "Form is not filled." << std::endl;
        }
    }
    _formToValidate.clear();
}

void Headmaster::attendYourCourse() {
    std::cout << "[Headmaster] " << _name << " launch the classes." << std::endl;
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->ensureCourse();
    }
    for (const auto& s : StudentList::getInstance().getList()) {
        s->ensureCourse();
    }
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->doClass();
    }
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
    Form* form = StaffList::getInstance().getSecretary()->createForm(FormType::NeedCourseCreation);
    dynamic_cast<NeedCourseCreationForm*>(form)->fill(p_courseName, this, p_numberOfClassToGraduate, p_maximumNumberOfStudent);
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Professor::requestMoreClassRoom(Course* p_course) {
    Form* form = StaffList::getInstance().getSecretary()->createForm(FormType::NeedMoreClassRoom);
    dynamic_cast<NeedMoreClassRoomForm*>(form)->fill(p_course, this);
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Professor::requestCourseFinished(Student* p_student, Course* p_course) {
    Form* form = StaffList::getInstance().getSecretary()->createForm(FormType::CourseFinished);
    dynamic_cast<CourseFinishedForm*>(form)->fill(p_student, p_course);
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Professor::ensureCourse() {
    std::cout << "[Professor] " << _name << " is ensuring course." << std::endl;
    if (_currentCourse == nullptr) {
        std::cout << "[Professor] " << _name << " check for course without professor." << std::endl;
        for (const auto& course : CourseList::getInstance().getList()) {
            if (course->getProfessor() == nullptr) {
                std::cout << "[Professor] " << _name << " assign course " << course->getName() << std::endl;
                assignCourse(course);
                return;
            }
        }
        std::cout << "No available courses to assign." << std::endl;
    }
    if (_currentCourse == nullptr) {
        std::cout << "[Professor] " << _name << " request a new course." << std::endl;
        requestCourseCreation(this->_name + "_course", 2, 25); // Example course creation
    }
}

void Professor::doClass() {
    if (_currentRoom == nullptr) {
        requestMoreClassRoom(_currentCourse);
    }
    
    std::set<Student*> studentToGraduate;
    std::cout << "[Professor] " << _name << " is doing class" << std::endl;
    for (const auto& s : _currentCourse->getStudents()) {
        s->attendClass(dynamic_cast<Classroom*>(_currentRoom));
        if (s->getSubscribedCourses().at(_currentCourse) == 0) {
            studentToGraduate.insert(s);
        }
    }

    for (const auto& s : studentToGraduate) {
        requestCourseFinished(s, _currentCourse);
    }
}

void Student::requestSubscriptionToCourse(Course* p_course) {
    Form* form = StaffList::getInstance().getSecretary()->createForm(FormType::SubscriptionToCourse);
    dynamic_cast<SubscriptionToCourseForm*>(form)->fill(this, p_course);
    Headmaster* headmaster = StaffList::getInstance().getHeadmaster();
    headmaster->receiveForm(form);
    headmaster->sign();
    form->execute();
    delete form;
}

void Student::subscribe(Course* p_course) {
    if (_subscribedCourse.find(p_course) == _subscribedCourse.end()) {
        std::cout << "[Student] " << _name << " subscribed to course " << p_course->getName() << std::endl;
        _subscribedCourse[p_course] = p_course->getNumberOfClassToGraduate();
    } else {
        std::cout << "Already subscribed to course " << p_course->getName() << std::endl;
    }
}

void Student::unsubscribe(Course* p_course) {
    if (_subscribedCourse.find(p_course) != _subscribedCourse.end()) {
        std::cout << "[Student] " << _name << " unsubscribed from course " << p_course->getName() << std::endl;
        _subscribedCourse.erase(p_course);
    } else {
        std::cout << "Not subscribed to course " << p_course->getName() << std::endl;
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
        std::cout << "No available courses to subscribe." << std::endl;
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