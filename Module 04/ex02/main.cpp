#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include "List.hpp"

int main() {
    StaffList& staffList = StaffList::getInstance();
    StudentList& studentList = StudentList::getInstance();
    CourseList& courseList = CourseList::getInstance();
    RoomList& roomList = RoomList::getInstance();
    
    Secretary* secretary = new Secretary("Bob");
    staffList.addToList(secretary);
    Headmaster* headmaster = new Headmaster("Bob");
    staffList.addToList(headmaster);
    Student* student = new Student("Bob");
    studentList.addToList(student);

    Course* math = new Course("Mathematics");
    courseList.addToList(math);

    Form* form1 = secretary->createForm(FormType::CourseFinished);
    Form* form4 = secretary->createForm(FormType::SubscriptionToCourse);

    static_cast<CourseFinishedForm*>(form1)->fillForm(math);
    static_cast<SubscriptionToCourseForm*>(form4)->fillForm(student, math);

    headmaster->sign(form1);
    headmaster->sign(form4);

    form1->execute();
    form4->execute();

    delete form1;
    delete form4;

    return 0;
}
