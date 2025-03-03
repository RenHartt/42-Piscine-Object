#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"
#include "Singleton.hpp"
#include <iostream>

int main() {
    StudentList& studentList = StudentList::getInstance();
    StaffList& staffList = StaffList::getInstance();
    CourseList& courseList = CourseList::getInstance();
    RoomList& roomList = RoomList::getInstance();

    std::shared_ptr<Student> student1 = std::make_shared<Student>("Alice");
    std::shared_ptr<Student> student2 = std::make_shared<Student>("Bob");
    studentList.addToList(student1);
    studentList.addToList(student2);

    std::shared_ptr<Professor> prof1 = std::make_shared<Professor>("Dr. Brown");
    std::shared_ptr<Professor> prof2 = std::make_shared<Professor>("Prof. Wilson");
    staffList.addToList(prof1);
    staffList.addToList(prof2);

    std::shared_ptr<Course> course1 = std::make_shared<Course>("Mathematics");
    std::shared_ptr<Course> course2 = std::make_shared<Course>("Physics");
    course1->assign(prof1);
    course2->assign(prof2);
    courseList.addToList(course1);
    courseList.addToList(course2);

    course1->subscribe(student1);
    course2->subscribe(student2);
    course1->subscribe(student2);

    std::shared_ptr<Classroom> room1 = std::make_shared<Classroom>();
    std::shared_ptr<Classroom> room2 = std::make_shared<Classroom>();
    roomList.addToList(room1);
    roomList.addToList(room2);

    std::cout << "--- Récapitulatif des données ---" << std::endl;

    std::cout << "Nombre d'étudiants : " << studentList.getList().size() << std::endl;
    std::cout << "Nombre de professeurs : " << staffList.getList().size() << std::endl;
    std::cout << "Nombre de cours : " << courseList.getList().size() << std::endl;
    std::cout << "Nombre de salles : " << roomList.getList().size() << std::endl;

    return 0;
}
