#pragma once

#include <string>

class Course;
class Student;
class Secretary;
class Headmaster;

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

    friend Headmaster;
    
protected:
    Form(FormType p_formType);
    
    void setFilled(bool state);
    void signForm();
    
public:
    virtual ~Form();

    bool isSigned() const;
    bool isFilled() const;
    FormType getFormType();

    virtual void execute() = 0;
};

class CourseFinishedForm : public Form {
private:
    Course* _course;

    friend Secretary;

    CourseFinishedForm();
public:
    
    void fillForm(Course* course);
    void execute() override;
};

class NeedMoreClassRoomForm : public Form {
private:
    NeedMoreClassRoomForm();

    friend Secretary;
public:    
    
    void fillForm();
    void execute() override;
};

class NeedCourseCreationForm : public Form {
private:
    std::string _courseName;

    NeedCourseCreationForm();

    friend Secretary;
public:
    
    void fillForm(const std::string& courseName);
    void execute() override;
};

class SubscriptionToCourseForm : public Form {
private:
    Student* _student;
    Course* _course;
    
    SubscriptionToCourseForm();

    friend Secretary;
public:    
    
    void fillForm(Student* student, Course* course);
    void execute() override;
};    