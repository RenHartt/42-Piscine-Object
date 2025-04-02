#include <iostream>

#include "Singleton.hpp"
#include "Course.hpp"
#include "Event.hpp"
#include "Form.hpp"
#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"

int main() {
    auto& staffList = StaffList::getInstance();
    auto& studentList = StudentList::getInstance();
    auto& courseList = CourseList::getInstance();
    auto& roomList = RoomList::getInstance();

    Headmaster* headmaster = new Headmaster("Dumbledore");
    Secretary* secretary = new Secretary("Ms. Penny");
    Professor* professor = new Professor("Professor Oak");
    Student* student = new Student("Ash Ketchum");

    staffList.addToList(headmaster);
    staffList.addToList(secretary);
    staffList.addToList(professor);
    studentList.addToList(student);

    std::cout << "\n--- Professor demande la création d'un cours ---\n";
    Form* creationForm = professor->requestCourseCreationForm("Potions", secretary);
    headmaster->receiveForm(creationForm);
    headmaster->sign(creationForm);
    creationForm->execute(headmaster);

    std::cout << "\n--- Student demande à s'inscrire à ce cours ---\n";
    Course* potions = CourseList::getInstance().getFromList("Potions");
    if (!potions) {
        std::cerr << "Erreur : le cours Potions n'existe pas." << std::endl;
        return 1;
    }

    Form* subscriptionForm = student->requestSubscriptionToCourseForm(potions, secretary);
    headmaster->receiveForm(subscriptionForm);
    headmaster->sign(subscriptionForm);
    subscriptionForm->execute(headmaster);

    std::cout << "\n--- Professor demande une salle pour son cours ---\n";
    Form* classroomRequest = secretary->createForm(FormType::NeedMoreClassRoom);
    static_cast<NeedMoreClassRoomForm*>(classroomRequest)->fill(potions);
    headmaster->receiveForm(classroomRequest);
    headmaster->sign(classroomRequest);
    classroomRequest->execute(headmaster);

    std::cout << "\n--- Vérification des salles disponibles ---\n";
    RoomList::getInstance().printList();
    std::cout << "\n--- Vérification des cours disponibles ---\n";
    CourseList::getInstance().printList();
    std::cout << "\n--- Vérification des étudiants disponibles ---\n";
    StudentList::getInstance().printList();
    std::cout << "\n--- Vérification des membres du personnel disponibles ---\n";
    StaffList::getInstance().printList();

    delete creationForm;
    delete subscriptionForm;
    delete classroomRequest;

    return 0;
}