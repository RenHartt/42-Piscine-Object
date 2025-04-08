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

    Professor* p_professor = p_course->getProfessor();
    Classroom* p_classroom = p_course->getClassroom();

    for (const auto& student : p_course->getStudents()) {
        student->exitRoom();
        p_classroom->exit(student);
        if (student->getSubscribedCourses()[p_course] == 0) {
            student->graduate(p_course);
        }
    }
    p_professor->exitRoom();
    p_classroom->exit(p_professor);
    p_classroom->assignCourse(nullptr);
    p_course->setClassroom(nullptr);
}

void Headmaster::processNeedMoreClassRoom(Course* p_course) {
    std::cout << "[Headmaster] creating new classroom for course " << p_course->getName() << "." << std::endl;
    
    Classroom* newRoom = new Classroom();
    p_course->setClassroom(newRoom);
    newRoom->assignCourse(p_course);
    newRoom->enter(p_course->getProfessor());
    p_course->getProfessor()->enterRoom(newRoom);
    for (const auto& student : p_course->getStudents()) {
        newRoom->enter(student);
        student->enterRoom(newRoom);
    }
    RoomList::getInstance().addToList(newRoom);
}

void Headmaster::processNeedCourseCreation(std::string p_courseName, Professor* p_professor, int p_maxStudent, int p_nbrGraduate) {
    std::cout << "[Headmaster] Creating course: " << p_courseName << " for professor " << p_professor->getName() << "." << std::endl;

    Course* newCourse = new Course(p_courseName, p_maxStudent, p_nbrGraduate);
    newCourse->assign(p_professor);
    p_professor->assignCourse(newCourse);
    CourseList::getInstance().addToList(newCourse);
}

void Headmaster::processSubscriptionToCourse(Student* p_student, Course* p_course) {
    std::cout << "[Headmaster] Subscribing student " << p_student->getName() << " to course " << p_course->getName() << "." << std::endl;
    
    p_course->subscribe(p_student);
    p_student->subscribeToCourse(p_course);
}

void Headmaster::ensureProfessorHasCourse(Professor* p_professor) {
    if (p_professor->course() != nullptr)
        return;
    
    for (Course* c : CourseList::getInstance().getList()) {
        if (c->getProfessor() == nullptr) {
            c->assign(p_professor);
            p_professor->assignCourse(c);
            std::cout << "[Headmaster] Assigned existing course \"" << c->getName()
                      << "\" to professor " << p_professor->getName() << "." << std::endl;
            return;
        }
    }
    std::string autoCourseName = "AutoCourse_" + p_professor->getName();
    std::cout << "[Headmaster] No course available for professor " << p_professor->getName()
              << ". Creating new course: " << autoCourseName << std::endl;
    processNeedCourseCreation(autoCourseName, p_professor, 30, 5);
}

void Headmaster::ensureProfessorHasRoom(Professor* p_professor) {
    if (p_professor->room() != nullptr)
        return;
    
    for (Room* r : RoomList::getInstance().getList()) {
        Classroom* cls = dynamic_cast<Classroom*>(r);
        if (cls && cls->getCourse() == nullptr) {
            cls->assignCourse(p_professor->course());
            p_professor->enterRoom(r);
            std::cout << "[Headmaster] Assigned room ID " << r->getID()
                      << " to professor " << p_professor->getName() << "." << std::endl;
            return;
        }
    }
    std::cout << "[Headmaster] No room available for professor " << p_professor->getName() << ". Creating a new room." << std::endl;
    processNeedMoreClassRoom(p_professor->course());
}

void Headmaster::ensureStudentHasCourse(Student* p_student) {
    if (!p_student->getSubscribedCourses().empty())
        return;
    
    for (Course* c : CourseList::getInstance().getList()) {
        if (c->getProfessor() != nullptr) {
            processSubscriptionToCourse(p_student, c);
            return;
        }
    }
    std::cout << "[Headmaster] No course available for student " << p_student->getName() << "." << std::endl;
}

void Headmaster::ensureAllStudentsHasCourse() {
    for (Student* s : StudentList::getInstance().getList()) {
        ensureStudentHasCourse(s);
    }
}

void Headmaster::requireProfessorToDoClass(Professor* p_professor) {
    std::cout << "[Headmaster] Requiring professor " << p_professor->getName() << " to do class." << std::endl;

    ensureProfessorHasCourse(p_professor);
    ensureProfessorHasRoom(p_professor);
    
    for (Student* s : StudentList::getInstance().getList()) {
        if (s->getSubscribedCourses().find(p_professor->course()) != s->getSubscribedCourses().end()) {
            s->enterRoom(p_professor->room());
        }
    }
    
    p_professor->doClass();
    
    processCourseFinished(p_professor->course());
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

Form* Professor::requestCourseCreationForm(Secretary* p_secretary, std::string p_courseName, int p_maxStudent, int p_nbrGraduate) {
    std::cout << "[Professor] Requesting course creation: " << p_courseName << std::endl;
    Form* form = p_secretary->createForm(FormType::NeedCourseCreation);
    static_cast<NeedCourseCreationForm*>(form)->fill(p_courseName, this, p_maxStudent, p_nbrGraduate);
    return form;
}

void Professor::doClass() {
    if (_currentCourse != nullptr) {
        std::cout << "[Professor] Doing class for course: " << _currentCourse->getName() << std::endl;
        for (const auto& s : _currentCourse->getStudents()) {
            s->getSubscribedCourses()[_currentCourse]--;
        }
    } else {
        std::cout << "[Professor] No course assigned." << std::endl;
    }
}

Form* Student::requestSubscriptionToCourseForm(Course* p_course, Secretary* p_secretary) {
    std::cout << "[Student] Requesting subscription to course: " << p_course->getName() << std::endl;
    Form* form = p_secretary->createForm(FormType::SubscriptionToCourse);
    static_cast<SubscriptionToCourseForm*>(form)->fill(this, p_course);
    return form;
}

void Student::subscribeToCourse(Course* p_course) {
    _subscribedCourse[p_course] = p_course->getNumberOfClassToGraduate(); 
}

void Student::unsubscribeToCourse(Course* p_course) {
    _subscribedCourse.erase(p_course); 
}

std::map<Course*, int>& Student::getSubscribedCourses() {
    return _subscribedCourse; 
}

void Student::attendClass(Classroom* p_classroom) {
    if (p_classroom->canEnter(this)) {
        p_classroom->enter(this);
        this->enterRoom(p_classroom);
    } else {
        std::cout << "Classroom is full." << std::endl;
    }
}

void Student::exitClass() {
    _currentRoom->exit(this);
    this->exitRoom();
}

void Student::graduate(Course* p_course) {
    if (_subscribedCourse.find(p_course) != _subscribedCourse.end()) {
        _subscribedCourse.erase(p_course);
        p_course->unsubscribe(this);
        std::cout << "Student: " << this->getName() << " has been graduated from " << p_course->getName() << std::endl;
    } else {
        std::cout << "No course found in student subscribed courses" << std::endl;
    }
}