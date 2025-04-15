#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    Headmaster& headmaster = Headmaster::getInstance();
    Secretary& secretary = Secretary::getInstance();
    Professor* professor = new Professor("Professor");
    Student* student = new Student("Student");

    std::cout << "Starting simulation..." << std::endl;

    std::cout << std::endl;

    Form* creationForm = secretary.createForm(FormType::NeedCourseCreation);
    dynamic_cast<NeedCourseCreationForm*>(creationForm)->fill("Math", professor, 2, 25);
    headmaster.receiveForm(creationForm);
    headmaster.sign();
    creationForm->execute();

    std::cout << std::endl;

    Course* mathCourse = CourseList::getInstance().getFromList("Math");
    Form* classRoomForm = secretary.createForm(FormType::NeedMoreClassRoom);
    dynamic_cast<NeedMoreClassRoomForm*>(classRoomForm)->fill(mathCourse);
    headmaster.receiveForm(classRoomForm);
    headmaster.sign();
    classRoomForm->execute();

    std::cout << std::endl;

    Form* subscriptionForm = secretary.createForm(FormType::SubscriptionToCourse);
    dynamic_cast<SubscriptionToCourseForm*>(subscriptionForm)->fill(student, mathCourse);
    headmaster.receiveForm(subscriptionForm);
    headmaster.sign();
    subscriptionForm->execute();

    std::cout << std::endl;

    Form* graduationForm = secretary.createForm(FormType::CourseFinished);
    dynamic_cast<CourseFinishedForm*>(graduationForm)->fill(mathCourse);
    headmaster.receiveForm(graduationForm);
    headmaster.sign();
    graduationForm->execute();

    std::cout << "\n--- Staff List ---" << std::endl;
    StaffList::getInstance().printList();

    std::cout << "\n--- Student List ---" << std::endl;
    StudentList::getInstance().printList();

    std::cout << "\n--- Room List ---" << std::endl;
    RoomList::getInstance().printList();

    std::cout << "\n--- Course List ---" << std::endl;
    CourseList::getInstance().printList();

    // Nettoyage mémoire
    delete creationForm;
    delete classRoomForm;
    delete subscriptionForm;
    delete graduationForm;

    return 0;
}
