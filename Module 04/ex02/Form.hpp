#pragma once

enum class FormType {
    CourseFinished,
    NeedMoreClassRoom,
    NeedCourseCreation,
    SubscriptionToCourse
};

class Form {
private:
    FormType _formType;
    bool _isSigned = false;

public:
    Form(FormType p_formType) : _formType(p_formType) {}
    virtual ~Form() {}

    virtual void execute() = 0;
};

class CourseFinishedForm : public Form {
public:
    CourseFinishedForm() : Form(FormType::CourseFinished) {}
    void execute() override {}
};

class NeedMoreClassRoomForm : public Form {
public:
    NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
    void execute() override {}
};

class NeedCourseCreationForm : public Form {
public:
    NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
    void execute() override {}
};

class SubscriptionToCourseForm : public Form {
public:
    SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
    void execute() override {}
};