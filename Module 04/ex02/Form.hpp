#pragma once

#include <string>

class Course;
class Student;

enum class FormType {
    CourseFinished,
    NeedMoreClassRoom,
    NeedCourseCreation,
    SubscriptionToCourse
};

class Form {
private:
    FormType _formType;
    bool _signed;
    bool _isFilled;

    friend class Headmaster;
    
    protected:
    void setFilled(bool state);
    void signForm();
    
public:
    Form(FormType p_formType);
    virtual ~Form();

    virtual void execute() = 0;

    bool isSigned() const;
    bool isFilled() const;
    FormType getFormType();
};

class CourseFinishedForm : public Form {
private:
    Course* _course;

public:    
    CourseFinishedForm();
    
    void fillForm(Course* course);
    void execute() override;
};

class NeedMoreClassRoomForm : public Form {
private:

public:    
    NeedMoreClassRoomForm();
    
    void fillForm();
    void execute() override;
};

class NeedCourseCreationForm : public Form {
private:
    std::string _courseName;

public:
    NeedCourseCreationForm();
    
    void fillForm(const std::string& courseName);
    void execute() override;
};

class SubscriptionToCourseForm : public Form {
private:
    Student* _student;
    Course* _course;

public:    
    SubscriptionToCourseForm();
    
    void fillForm(Student* student, Course* course);
    void execute() override;
};    