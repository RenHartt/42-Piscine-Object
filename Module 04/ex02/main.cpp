#include "Person.hpp"
#include "Form.hpp"
#include "Course.hpp"
#include "Room.hpp"

int main() {
    Secretary* secretary = new Secretary("Bob");
    Headmaster* headmaster = new Headmaster("Bob");
    Student* student = new Student("Bob");

    Course* math = new Course("Mathematics");

    CourseFinishedForm* form1 = new CourseFinishedForm();
    SubscriptionToCourseForm* form4 = new SubscriptionToCourseForm();
    
    form1->fillForm(math);
    form4->fillForm(student, math);

    headmaster->sign(form1);
    headmaster->sign(form4);

    form1->execute();
    form4->execute();

    return 0;
}
