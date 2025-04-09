#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "List.hpp"
#include "Room.hpp"

#include <iostream>

Headmaster* Person::callHeadmaster() {
    Headmaster* headmaster = nullptr;
    for (const auto& staff : StaffList::getInstance().getList()) {
        headmaster = dynamic_cast<Headmaster*>(staff);
        if (headmaster) {
            break;
        }
    }
    return headmaster;
}

void Person::exitRoom() {
    _currentRoom->exit(this);
    _currentRoom = nullptr;
}

void Person::enterRoom(Room* p_room) {
    p_room->enter(this);
    _currentRoom = p_room;
}

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

void Headmaster::assignProfessorToCourse(Professor* p_professor, Course* p_course) {
    p_course->assignProfessor(p_professor);
    p_professor->assignCourse(p_course);
}

void Headmaster::assignStudentToCourse(Student* p_student, Course* p_course) {
    p_course->addStudent(p_student);
    p_student->subscribeToCourse(p_course);
}

void Headmaster::assignClassroomToCourse(Classroom* p_classroom, Course* p_course) {
    p_course->assignClassroom(p_classroom);
    p_classroom->assignCourse(p_course);
}

void Headmaster::assignClassroomToProfessor(Classroom* p_classroom, Professor* p_professor) {
    p_professor->enterRoom(p_classroom);
    p_classroom->enter(p_professor);
}

void Headmaster::assignClassroomToStudent(Classroom* p_classroom, Student* p_student) {
    p_student->enterRoom(p_classroom);
    p_classroom->enter(p_student);
}

void Headmaster::unassignProfessorFromCourse(Professor* p_professor, Course* p_course) {
    p_course->removeProfessor();
    p_professor->removeCourse();
}

void Headmaster::unassignStudentFromCourse(Student* p_student, Course* p_course) {
    p_course->removeStudent(p_student);
    p_student->unsubscribeToCourse(p_course);
}

void Headmaster::unassignCourseFromClassroom(Classroom* p_classroom, Course* p_course) {
    p_course->removeClassroom();
    p_classroom->removeCourse();
}

void Headmaster::processCourseFinished(Course* p_course) {
    std::cout << "Course " << p_course->getName() << " has finished." << std::endl;

    Classroom* p_classroom = p_course->getClassroom();
    std::set<Student*> studentsCopy = p_course->getStudents();
    for (const auto& student : studentsCopy) {
        student->exitRoom();
        if (student->getSubscribedCourses()[p_course] == 0) {
            student->graduate(p_course);
        }
    }
    p_course->getProfessor()->exitRoom();
    unassignCourseFromClassroom(p_classroom, p_course);
}

void Headmaster::processNeedMoreClassRoom(Course* p_course) {
    std::cout << "[Headmaster] creating new classroom for course " << p_course->getName() << "." << std::endl;
    
    Classroom* newRoom = new Classroom();
    assignClassroomToCourse(newRoom, p_course);
    assignClassroomToProfessor(newRoom, p_course->getProfessor());
    for (const auto& student : p_course->getStudents()) {
        assignClassroomToStudent(newRoom, student);
    }
    RoomList::getInstance().addToList(newRoom);
}

void Headmaster::processNeedCourseCreation(std::string p_courseName, Professor* p_professor, int p_maxStudent, int p_nrequiredClassesToGraduate) {
    std::cout << "[Headmaster] Creating course: " << p_courseName << " for professor " << p_professor->getName() << "." << std::endl;

    Course* newCourse = new Course(p_courseName, p_maxStudent, p_nrequiredClassesToGraduate);
    assignProfessorToCourse(p_professor, newCourse);
    CourseList::getInstance().addToList(newCourse);
}

void Headmaster::processSubscriptionToCourse(Student* p_student, Course* p_course) {
    std::cout << "[Headmaster] Subscribing student " << p_student->getName() << " to course " << p_course->getName() << "." << std::endl;
    
    assignStudentToCourse(p_student, p_course);
}

void Headmaster::ensureProfessorHasCourse(Professor* p_professor) {
    if (p_professor->course() != nullptr)
        return;
    
    for (Course* c : CourseList::getInstance().getList()) {
        if (c->getProfessor() == nullptr) {
            assignProfessorToCourse(p_professor, c);
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
        if (cls && cls->assignedCourse() == nullptr) {
            assignClassroomToProfessor(cls, p_professor);
            assignClassroomToCourse(cls, p_professor->course());
            std::cout << "[Headmaster] Assigned room ID " << r->getID() << " to professor " << p_professor->getName() << "." << std::endl;
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
            assignStudentToCourse(p_student, c);
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

    Course* p_course = p_professor->course();
    Classroom* p_classroom = p_course->getClassroom();
    for (const auto& student : p_course->getStudents()) {
        assignClassroomToStudent(p_classroom, student);
    }

    p_professor->doClass();
    p_professor->closeCourse();
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

void Professor::doClass() {
    if (!_currentCourse) {
        std::cout << "[Professor] No course assigned." << std::endl;
        return;
    } else if (_currentCourse->getClassroom() == nullptr) {
        std::cout << "[Professor] No classroom assigned." << std::endl;
        return;
    } else if (_currentCourse->getStudents().empty()) {
        std::cout << "[Professor] No students enrolled." << std::endl;
        return;
    }
    
    std::cout << "[Professor] Doing class for course: " << _currentCourse->getName() << std::endl;
    for (const auto& s : _currentCourse->getStudents()) {
        s->attendCourse(_currentCourse);
    }
}

void Professor::closeCourse() {
    Headmaster* headmaster = callHeadmaster();
    if (headmaster) {
        headmaster->processCourseFinished(_currentCourse);
    } else {
        std::cout << "[Professor] No headmaster available." << std::endl;
    }
}

Form* Professor::requestCourseCreationForm(Secretary* p_secretary, std::string p_courseName, int p_maxStudent, int p_nrequiredClassesToGraduate) {
    std::cout << "[Professor] Requesting course creation: " << p_courseName << std::endl;
    Form* form = p_secretary->createForm(FormType::NeedCourseCreation);
    static_cast<NeedCourseCreationForm*>(form)->fill(p_courseName, this, p_maxStudent, p_nrequiredClassesToGraduate);
    return form;
}

Form* Student::requestSubscriptionToCourseForm(Course* p_course, Secretary* p_secretary) {
    const std::string& courseName = p_course ? p_course->getName() : "null";
    std::cout << "[Student] Requesting subscription to course: " << courseName << std::endl;
    Form* form = p_secretary->createForm(FormType::SubscriptionToCourse);
    static_cast<SubscriptionToCourseForm*>(form)->fill(this, p_course);
    return form;
}

void Student::subscribeToCourse(Course* p_course) {
    _subscribedCourse[p_course] = p_course->requiredClassesToGraduate(); 
}

void Student::unsubscribeToCourse(Course* p_course) {
    _subscribedCourse.erase(p_course); 
}

bool Student::isSubscribedToCourse(Course* p_course) const { 
    return _subscribedCourse.count(p_course) > 0; 
}

std::map<Course*, int>& Student::getSubscribedCourses() {
    return _subscribedCourse; 
}

void Student::attendClass(Classroom* p_classroom) {
    if (p_classroom->canEnter(this)) {
        this->enterRoom(p_classroom);
    } else {
        std::cout << "[Student] Classroom is full." << std::endl;
    }
}

void Student::attendCourse(Course* p_course) {
    if (isSubscribedToCourse(p_course)) {
        _subscribedCourse[p_course]--;
    }
}

void Student::exitClass() {
    this->exitRoom();
}

void Student::graduate(Course* p_course) {
    if (_subscribedCourse.find(p_course) != _subscribedCourse.end()) {
        _subscribedCourse.erase(p_course);
        p_course->removeStudent(this);
        std::cout << "[Student] " << this->getName() << " has been graduated from " << p_course->getName() << std::endl;
    } else {
        std::cout << "[Student] No course found in student subscribed courses" << std::endl;
    }
}