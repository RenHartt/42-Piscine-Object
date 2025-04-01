#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    auto& staffList = StaffList::getInstance();
    auto& studentList = StudentList::getInstance();
    auto& courseList = CourseList::getInstance();
    auto& roomList = RoomList::getInstance();

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

    staffList.addToList(headmaster);
    staffList.addToList(secretary);
    staffList.addToList(professor1);
    staffList.addToList(professor2);
    studentList.addToList(student1);
    studentList.addToList(student2);
    courseList.addToList(course1);
    courseList.addToList(course2);
    roomList.addToList(classroom1);
    roomList.addToList(classroom2);
    roomList.addToList(secretarialOffice);
    roomList.addToList(headmasterOffice);
    roomList.addToList(staffRestRoom);

    std::cout << "Staff List:" << std::endl;
    staffList.printList();
    std::cout << "Student List:" << std::endl;
    studentList.printList();
    std::cout << "Course List:" << std::endl;
    courseList.printList();
    std::cout << "Room List:" << std::endl;
    roomList.printList();

    return 0;
}
