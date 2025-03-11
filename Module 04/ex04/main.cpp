#include "Course.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    // Création des listes Singletons
    auto& studentList = StudentList::getInstance();
    auto& courseList = CourseList::getInstance();
    auto& staffList = StaffList::getInstance();
    auto& roomList = RoomList::getInstance();

    // Création des objets principaux
    auto headmaster = std::make_shared<Headmaster>("Dr. Smith");
    auto secretary = std::make_shared<Secretary>("Mrs. Johnson");

    auto student = std::make_shared<Student>("Alice");
    auto professor = std::make_shared<Professor>("Dr. Brown");
    auto course = std::make_shared<Course>("Mathematics");

    // Ajout des objets aux listes
    studentList.addToList(student);
    courseList.addToList(course);
    staffList.addToList(professor);

    // 📌 Création et gestion d'un formulaire "Fin de Cours"
    auto courseFinishedForm = std::static_pointer_cast<CourseFinishedForm>(
        secretary->createForm(FormType::CourseFinished));
    courseFinishedForm->fillForm(student, course);

    headmaster->receiveForm(courseFinishedForm);  // Signe et exécute

    // 📌 Création et gestion d'un formulaire "Besoin de Salle"
    auto needRoomForm = std::static_pointer_cast<NeedMoreClassRoomForm>(
        secretary->createForm(FormType::NeedMoreClassRoom));
    needRoomForm->fillForm(2, "More students enrolled");

    headmaster->receiveForm(needRoomForm);  // Signe et exécute

    // 📌 Création et gestion d'un formulaire "Création de Cours"
    auto needCourseForm = std::static_pointer_cast<NeedCourseCreationForm>(
        secretary->createForm(FormType::NeedCourseCreation));
    auto newCourse = std::make_shared<Course>("Physics");
    auto newProfessor = std::make_shared<Professor>("Dr. Einstein");
    needCourseForm->fillForm(newCourse, newProfessor);

    headmaster->receiveForm(needCourseForm);  // Signe et exécute

    // 📌 Création et gestion d'un formulaire "Inscription à un Cours"
    auto subscriptionForm = std::static_pointer_cast<SubscriptionToCourseForm>(
        secretary->createForm(FormType::SubscriptionToCourse));
    subscriptionForm->fillForm(student, newCourse);

    headmaster->receiveForm(subscriptionForm);  // Signe et exécute

    return 0;
}
