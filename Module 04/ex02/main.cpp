#include "Person.hpp"
#include "Form.hpp"
#include <iostream>
#include <memory>

int main() {
    Headmaster headmaster("M. Dupont");
    Secretary secretary("Mme Martin");

    std::cout << "Le secrétaire a créer trois formulaires.\n" << std::endl;

    std::shared_ptr<Form> form1 = secretary.createForm(FormType::NeedCourseCreation);
    std::shared_ptr<Form> form2 = secretary.createForm(FormType::SubscriptionToCourse);
    std::shared_ptr<Form> form3 = secretary.createForm(FormType::NeedMoreClassRoom);

    std::cout << "Le secrétaire envoie les formulaires au directeur..." << std::endl;

    headmaster.receiveForm(form1);
    headmaster.receiveForm(form2);
    headmaster.receiveForm(form3);

    std::cout << "\nTous les formulaires ont été traités !" << std::endl;

    return 0;
}
