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
    new Professor("Professor");
    new Course("math", nullptr, 2, 5);
    for (int i = 0; i < 10; ++i) {
        new Student("Student_" + std::to_string(i));
    }

    headmaster->attendYourCourse();

    return 0;
}
