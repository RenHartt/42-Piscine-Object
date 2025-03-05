#include "Person.hpp"
#include "Form.hpp"
#include <memory>

int main() {
    std::shared_ptr<Secretary> secretary = std::make_shared<Secretary>("Alice");
    std::shared_ptr<Headmaster> headmaster = std::make_shared<Headmaster>("Mr. Smith");

    std::cout << "===== Création des formulaires =====" << std::endl;
    
    std::shared_ptr<Form> courseFinished = secretary->createForm(FormType::CourseFinished);
    std::shared_ptr<Form> needMoreClassroom = secretary->createForm(FormType::NeedMoreClassRoom);
    std::shared_ptr<Form> needCourseCreation = secretary->createForm(FormType::NeedCourseCreation);
    std::shared_ptr<Form> subscriptionToCourse = secretary->createForm(FormType::SubscriptionToCourse);

    std::cout << "===== Tentative de signature AVANT remplissage =====" << std::endl;
    headmaster->sign(courseFinished);
    headmaster->sign(needMoreClassroom);
    headmaster->sign(needCourseCreation);
    headmaster->sign(subscriptionToCourse);

    std::cout << "===== Remplissage des formulaires =====" << std::endl;

    if (courseFinished) {
        std::dynamic_pointer_cast<CourseFinishedForm>(courseFinished)->fillForm("Bob", "Mathematics");
    }
    if (needMoreClassroom) {
        std::dynamic_pointer_cast<NeedMoreClassRoomForm>(needMoreClassroom)->fillForm(3, "New students enrolled");
    }
    if (needCourseCreation) {
        std::dynamic_pointer_cast<NeedCourseCreationForm>(needCourseCreation)->fillForm("Physics", "Dr. Johnson");
    }
    if (subscriptionToCourse) {
        std::dynamic_pointer_cast<SubscriptionToCourseForm>(subscriptionToCourse)->fillForm("Alice", "Programming 101");
    }

    std::cout << "===== Tentative de signature APRÈS remplissage =====" << std::endl;
    headmaster->sign(courseFinished);
    headmaster->sign(needMoreClassroom);
    headmaster->sign(needCourseCreation);
    headmaster->sign(subscriptionToCourse);

    std::cout << "===== Exécution des formulaires signés =====" << std::endl;
    headmaster->receiveForm(courseFinished);
    headmaster->receiveForm(needMoreClassroom);
    headmaster->receiveForm(needCourseCreation);
    headmaster->receiveForm(subscriptionToCourse);

    std::cout << "===== TEST TERMINÉ =====" << std::endl;

    return 0;
}
