#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    auto headmaster = new Headmaster("Headmaster");
    auto secretary = new Secretary("Secretary");
    auto professor = new Professor("Professor");
    auto student = new Student("Student");
    auto course = new Course("Math");
    
    Form* courseFinishedForm = secretary->createForm(FormType::CourseFinished);
    Form* needMoreClassRoomForm = secretary->createForm(FormType::NeedMoreClassRoom);
    Form* needCourseCreationForm = secretary->createForm(FormType::NeedCourseCreation);
    Form* subscriptionToCourseForm = secretary->createForm(FormType::SubscriptionToCourse);

    CourseFinishedForm* courseFinishedFormPtr = dynamic_cast<CourseFinishedForm*>(courseFinishedForm);
    NeedMoreClassRoomForm* needMoreClassRoomFormPtr = dynamic_cast<NeedMoreClassRoomForm*>(needMoreClassRoomForm);
    NeedCourseCreationForm* needCourseCreationFormPtr = dynamic_cast<NeedCourseCreationForm*>(needCourseCreationForm);
    SubscriptionToCourseForm* subscriptionToCourseFormPtr = dynamic_cast<SubscriptionToCourseForm*>(subscriptionToCourseForm);

    courseFinishedFormPtr->fill(course);
    needMoreClassRoomFormPtr->fill(course);
    needCourseCreationFormPtr->fill("Math", professor);
    subscriptionToCourseFormPtr->fill(student, course);

    headmaster->receiveForm(courseFinishedForm);
    headmaster->receiveForm(needMoreClassRoomForm);
    headmaster->receiveForm(needCourseCreationForm);
    headmaster->receiveForm(subscriptionToCourseForm);

    courseFinishedFormPtr->execute();
    needMoreClassRoomFormPtr->execute();
    needCourseCreationFormPtr->execute();
    subscriptionToCourseFormPtr->execute();

    headmaster->sign(courseFinishedForm);
    headmaster->sign(needMoreClassRoomForm);
    headmaster->sign(needCourseCreationForm);
    headmaster->sign(subscriptionToCourseForm);

    courseFinishedFormPtr->execute();
    needMoreClassRoomFormPtr->execute();
    needCourseCreationFormPtr->execute();
    subscriptionToCourseFormPtr->execute();

    delete courseFinishedForm;
    delete needMoreClassRoomForm;
    delete needCourseCreationForm;
    delete subscriptionToCourseForm;

    return 0;
}
