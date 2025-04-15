#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    new Headmaster("Headmaster");
    new Secretary("Secretary");
    new Professor("Professor1");
    new Professor("Professor2");
    new Student("Student1");
    new Student("Student2");
    new Course("Course1");
    new Course("Course2");
    new Classroom();
    new Classroom();
    new SecretarialOffice();
    new HeadmasterOffice();
    new StaffRestRoom();

    std::cout << "Staff List:" << std::endl;
    StaffList::getInstance().printList();
    std::cout << "Student List:" << std::endl;
    StudentList::getInstance().printList();
    std::cout << "Course List:" << std::endl;
    CourseList::getInstance().printList();
    std::cout << "Room List:" << std::endl;
    RoomList::getInstance().printList();

    return 0;
}
