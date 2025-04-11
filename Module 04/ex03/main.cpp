#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    Headmaster* headmaster = new Headmaster("Headmaster");
    new Secretary("Secretary");
    for (int i = 0; i < 5; ++i) {
        new Professor("Professor_" + std::to_string(i));
    }
    for (int i = 0; i < 10; ++i) {
        new Course("Course_" + std::to_string(i), nullptr, 5, 10);
    }
    new Classroom();
    for (int i = 0; i < 12; ++i) {
        new Student("Student_" + std::to_string(i));
        headmaster->attendYourCourse();
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
