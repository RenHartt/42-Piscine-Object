#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

#define STUDENT_NUMBER 10
#define PROFESSOR_NUMBER 2
#define COURSE_NUMBER 2
#define CLASSROOM_NUMBER 1

int main() {
    Headmaster* headmaster = new Headmaster("Headmaster");
    new Secretary("Secretary");
    for (int i = 0; i < PROFESSOR_NUMBER; ++i) {
        new Professor("Professor_" + std::to_string(i));
    }
    for (int i = 0; i < COURSE_NUMBER; ++i) {
        new Course("Course_" + std::to_string(i), nullptr, 5, 5);
    }
    for (int i = 0; i < CLASSROOM_NUMBER; ++i) {
        new Classroom();
    }
    for (int i = 0; i < STUDENT_NUMBER; ++i) {
        new Student("Student_" + std::to_string(i));
        headmaster->attendYourCourse();
        headmaster->finishYourCourse();
    }


    std::cout << "Staff List:" << std::endl;
    StaffList::getInstance().printList();
    std::cout << "Student List:" << std::endl;
    StudentList::getInstance().printList();
    std::cout << "Room List:" << std::endl;
    RoomList::getInstance().printList();
    std::cout << "Course List:" << std::endl;
    CourseList::getInstance().printList();

    return 0;
}
