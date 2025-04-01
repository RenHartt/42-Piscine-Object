#include "Person.hpp"
#include "Form.hpp"

#include <iostream>

void Headmaster::receiveForm(Form* p_form) {
    _formToValidate.insert(p_form);
}

void Headmaster::sign(Form* p_form) {
    if (p_form->isFilled()) {
        p_form->sign();
        std::cout << "Form signed by " << getName() << std::endl;
    } else {
        std::cout << "Form is not filled." << std::endl;
    }
}

Form* Secretary::createForm(FormType p_formType) {
    switch (p_formType) {
        case FormType::CourseFinished:
            return new CourseFinishedForm();
        case FormType::NeedMoreClassRoom:
            return new NeedMoreClassRoomForm();
        case FormType::NeedCourseCreation:
            return new NeedCourseCreationForm();
        case FormType::SubscriptionToCourse:
            return new SubscriptionToCourseForm();
        default:
            return nullptr;
    }
}