#pragma once

#include <iostream>
#include <memory>

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
        void setFilled(bool state) { _isFilled = state; }
        void signForm() { _signed = true; }
        
    public:
        Form(FormType p_formType) : _formType(p_formType), _signed(false), _isFilled(false) {}
        virtual ~Form() {}
        
        virtual void execute() = 0;
        
        bool isSigned() const { return _signed; }
        bool isFilled() const { return _isFilled; }
        FormType getFormType() { return _formType; }
};

class CourseFinishedForm : public Form {
    private:
        std::shared_ptr<Student> _student;
        std::shared_ptr<Course> _course;
        
    public:    
        CourseFinishedForm() : Form(FormType::CourseFinished) {}
        
        void fillForm(std::shared_ptr<Student> student, std::shared_ptr<Course> course) {
            _student = student;
            _course = course;
            setFilled(true);
            std::cout << "Course Finished Form filled for student: " << _student->getName() 
            << ", course: " << _course->getName() << std::endl;
        }
        
        void execute() override {
            if (isSigned()) {
                auto& courseList = CourseList::getInstance();
                courseList.removeFromList(_course);
                std::cout << "Course " << _course->getName() << " has been removed from the school.\n";
            } else {
                std::cout << "Form not signed." << std::endl;
            }
        }
};

class NeedMoreClassRoomForm : public Form {
    private:
        int _roomCount;
        std::string _reason;
        
    public:
        NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
        
        void fillForm(int roomCount, const std::string& reason) {
            _roomCount = roomCount;
            _reason = reason;
            setFilled(true);
            std::cout << "Need More Classroom Form filled. Rooms requested: " << _roomCount 
            << ", Reason: " << _reason << std::endl;
        }
        
        void execute() override {
            if (isSigned()) {
                auto& roomList = RoomList::getInstance();
                for (int i = 0; i < _roomCount; ++i) {
                    roomList.addToList(std::make_shared<Room>());
                }
                std::cout << _roomCount << " new classrooms have been created due to: " << _reason << "\n";
                } else {
                    std::cout << "Form not signed." << std::endl;
                }
            }
};

class NeedCourseCreationForm : public Form {
    private:
        std::shared_ptr<Course> _course;
        std::shared_ptr<Professor> _professor;
        
    public:    
        NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
        
        void fillForm(std::shared_ptr<Course> course, std::shared_ptr<Professor> professor) {
            _course = course;
            _professor = professor;
            setFilled(true);
            std::cout << "Need Course Creation Form filled. Course: " << _course->getName() 
            << ", Professor: " << _professor->getName() << std::endl;
        }
        
        void execute() override {
            if (isSigned()) {
                auto& staffList = StaffList::getInstance();
                auto& courseList = CourseList::getInstance();

                staffList.addToList(std::static_pointer_cast<Staff>(_professor));
                std::cout << "New professor added: " << _professor->getName() << "\n";
                courseList.addToList(_course);
                std::cout << "New course created: " << _course->getName() << " by professor " << _professor->getName() << ".\n";
            } else {
                std::cout << "Form not signed." << std::endl;
            }
        }
};

class SubscriptionToCourseForm : public Form {
    private:
        std::shared_ptr<Student> _student;
        std::shared_ptr<Course> _course;
    
    public:    
        SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
            
        void fillForm(std::shared_ptr<Student> student, std::shared_ptr<Course> course) {
            _student = student;
            _course = course;
            setFilled(true);
            std::cout << "Subscription to Course Form filled. Student: " << _student->getName() 
            << ", Course: " << _course->getName() << std::endl;
        }
        
        void execute() override {
            if (isSigned()) {
                auto& studentList = StudentList::getInstance();
                auto& courseList = CourseList::getInstance();
                
                _course->subscribe(_student);
                std::cout << _student->getName() << " has been successfully enrolled in "
                << _course->getName() << ".\n";
            } else {
                std::cout << "Form not signed." << std::endl;
            }
        }
};