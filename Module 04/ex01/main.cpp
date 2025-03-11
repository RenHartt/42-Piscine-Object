#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    StudentList& studentList = StudentList::getInstance();
    StaffList& staffList = StaffList::getInstance();
    CourseList& courseList = CourseList::getInstance();
    RoomList& roomList = RoomList::getInstance();

    Student student("Bob");
    Headmaster headmaster("Bob");
    Secretary secretary("Bob");
    Professor professor("Bob");
    Course course("Bob");
    Classroom classroom;
    SecretarialOffice secretarialOffice;
    HeadmasterOffice headmasterOffice;
    StaffRestRoom staffRestRoom;
    Courtyard courtyard;

    studentList.addList(&student);
    staffList.addList(&headmaster);
    staffList.addList(&secretary);
    staffList.addList(&professor);
    courseList.addList(&course);
    roomList.addList(&classroom);
    roomList.addList(&secretarialOffice);
    roomList.addList(&headmasterOffice);
    roomList.addList(&staffRestRoom);
    roomList.addList(&courtyard);

    auto students = studentList.getList();
    auto staffs = staffList.getList();
    auto courses = courseList.getList();
    auto rooms = roomList.getList();

    std::cout << "student list :" << std::endl;
    for (const auto& student : students) {
        std::cout << student->getName() << std::endl;
    }

    std::cout << "staff list :" << std::endl;
    for (const auto& staff : staffs) {
        std::cout << staff->getName() << std::endl;
    }

    std::cout << "course list :" << std::endl;
    for (const auto& course : courses) {
        std::cout << course << std::endl;
    }

    std::cout << "room list :" << std::endl;
    for (const auto& room : rooms) {
        std::cout << room << std::endl;
    }

    return 0;
}
