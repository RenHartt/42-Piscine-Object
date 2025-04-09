#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    auto headmaster = new Headmaster("Headmaster");
    auto secretary = new Secretary("Secretary");
    auto professor1 = new Professor("Professor1");
    auto professor2 = new Professor("Professor2");
    auto student1 = new Student("Student1");
    auto student2 = new Student("Student2");
    auto course1 = new Course("Course1");
    auto course2 = new Course("Course2");
    auto classroom1 = new Classroom(course1);
    auto classroom2 = new Classroom(course2);
    auto secretarialOffice = new SecretarialOffice();
    auto headmasterOffice = new HeadmasterOffice();
    auto staffRestRoom = new StaffRestRoom();

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
