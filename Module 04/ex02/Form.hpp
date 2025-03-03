#pragma once

#include <iostream>

class HeadMaster;

enum class FormType {
    CourseFinished,
    NeedMoreClassRoom,
    NeedCourseCreation,
    SubscriptionToCourse
};

class Form {
private:
    FormType _formType;
    
    friend class HeadMaster;
    public:
    Form(FormType p_formType) : _formType(p_formType) {}
    virtual ~Form() {}
    
    virtual void execute() = 0;
};

class CourseFinishedForm : public Form {
        CourseFinishedForm() : Form(FormType::CourseFinished) {}
        void execute() override {
            std::cout << "Le cours a été marqué comme terminé !" << std::endl;
        }
    };
    
    class NeedMoreClassRoomForm : public Form {
        NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
        void execute() override {
            std::cout << "Demande de salle supplémentaire envoyée !" << std::endl;
        }
    };
    
    class NeedCourseCreationForm : public Form {
        NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
        void execute() override {
            std::cout << "Demande de création de cours envoyée !" << std::endl;
        }
    };
    
    class SubscriptionToCourseForm : public Form {
        SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
        void execute() override {
            std::cout << "Inscription au cours effectuée !" << std::endl;
        }
    };    