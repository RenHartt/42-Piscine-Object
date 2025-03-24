#include "Person.hpp"
#include "List.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include <memory>

int main() {
    auto& studentList = StudentList::getInstance();
    auto& staffList = StaffList::getInstance();
    auto& courseList = CourseList::getInstance();
    auto& roomList = RoomList::getInstance();

    auto headmaster = std::make_shared<Headmaster>("Dr. Smith");
    auto secretary = std::make_shared<Secretary>("Mrs. Johnson");
    auto professor = std::make_shared<Professor>("Dr. Brown");
    auto student = std::make_shared<Student>("Alice");

    staffList.addToList(headmaster);
    staffList.addToList(secretary);
    staffList.addToList(professor);
    studentList.addToList(student);

    headmaster->createCourse(professor, "Mathematics");
    headmaster->subscribeStudent(student, "Mathematics");
    headmaster->requestClassroom(2, "Too many students");
    headmaster->graduateStudent(student, "Mathematics");

    for (const auto& course : courseList.getList()) {
        std::cout << course->getName() << std::endl;
    }

    for (const auto& room : roomList.getList()) {
        room->printOccupant();
    }

    for (const auto& student : studentList.getList()) {
        student->graduate(courseList.getList().front());
    }

    for (const auto& student : studentList.getList()) {
        std::cout << student->getName() << std::endl;
    }

    return 0;
}
