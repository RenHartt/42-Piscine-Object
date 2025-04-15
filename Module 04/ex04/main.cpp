#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    new Classroom();
    Courtyard::getInstance();
    StaffRestRoom::getInstance();
    Headmaster& headmaster = Headmaster::getInstance();
    Professor* professor1 = new Professor("Professor");
    Student* student1 = new Student("Student");
    new Course("Course");

    headmaster.attach(professor1);
    headmaster.attach(student1);

    for (int i = 0; i < 10; ++i) {
        headmaster.attendYourCourse();

        headmaster.notify(Event::RingBell);
        headmaster.notify(Event::RingBell);
        
        headmaster.notify(Event::RingBell);
        headmaster.notify(Event::RingBell);

        headmaster.notify(Event::RingBell);
        headmaster.notify(Event::RingBell);

        headmaster.finishYourCourse();
    }

    return 0;
}