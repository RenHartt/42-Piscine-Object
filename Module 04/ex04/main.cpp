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
    Secretary* secretary = new Secretary("Secretary");
    Professor* professor1 = new Professor("Professor");
    Student* student1 = new Student("Student");
    new SecretarialOffice();
    new HeadmasterOffice();
    new StaffRestRoom();
    new Courtyard();
    new Classroom();
    new Course("Course");

    headmaster->attach(professor1);
    headmaster->attach(student1);
    
    headmaster->attendYourCourse();

    headmaster->notify(Event::RingBell);
    headmaster->notify(Event::RingBell);

    headmaster->finishYourCourse();

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
