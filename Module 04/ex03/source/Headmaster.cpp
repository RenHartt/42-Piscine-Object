#include "Person.hpp"
#include "Form.hpp"

void Headmaster::sign() {
    for (auto form : _formToValidate) {
        if (form->isFilled()) {
            form->sign();
            std::cout << "[Headmaster] Form signed by " << getName() << std::endl;
        } else {
            std::cout << "[Headmaster] Form is not filled." << std::endl;
        }
    }
    _formToValidate.clear();
}

void Headmaster::attendYourCourse() {
    std::cout << "[Headmaster] " << _name << " launch the classes." << std::endl;
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->ensureCourse();
        p->ensureClassroom();
    }
    for (const auto& s : StudentList::getInstance().getList()) {
        s->ensureCourse();
    }
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->doClass();
    }
}

void Headmaster::finishYourCourse() {
    std::cout << "[Headmaster] " << _name << " finish the classes." << std::endl;
    for (const auto& p : StaffList::getInstance().getProfessors()) {
        p->closeCourse();
    }
}


Form* Headmaster::requestForm(FormType p_formType) {
    return StaffList::getInstance().getSecretary()->createForm(p_formType);
}