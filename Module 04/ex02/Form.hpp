#pragma once

#include <string>

class Course;
class Professor;
class Student;

enum class FormType
{
	CourseFinished,
	NeedMoreClassRoom,
	NeedCourseCreation,
	SubscriptionToCourse
};

class Form
{
private:
	FormType _formType;
	bool _isSigned = false;

public:
	Form(FormType p_formType) : _formType(p_formType) {}
	virtual ~Form() {}

	bool isSigned() const { return _isSigned; }
	void sign() { _isSigned = true; }

	virtual bool isFilled() const = 0;
	virtual void execute() const = 0;
};

class CourseFinishedForm : public Form
{
private:
	Course* _course;
public:
	CourseFinishedForm() : Form(FormType::CourseFinished) {}

	void fill(Course* p_course) { _course = p_course; }
	bool isFilled() const override { return _course != nullptr; }
	
	void execute() const override;
};

class NeedMoreClassRoomForm : public Form
{
private:
	Course* _course;
public:
	NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}

	void fill(Course* p_course) { _course = p_course; }
	bool isFilled() const override { return _course != nullptr; }
	
	void execute() const override;
};

class NeedCourseCreationForm : public Form
{
private:
	std::string _courseName;
	Professor* _professor;
public:
	NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}

	void fill(const std::string& p_courseName, Professor* p_professor)
	{
		_courseName = p_courseName;
		_professor = p_professor;
	}
	bool isFilled() const override { return !_courseName.empty() && _professor != nullptr; }
	
	void execute() const override;
};

class SubscriptionToCourseForm : public Form
{
private:
	Student* _student;
	Course* _course;
public:
	SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}

	void fill(Student* p_student, Course* p_course)
	{
		_student = p_student;
		_course = p_course;
	}
	bool isFilled() const override { return _student != nullptr && _course != nullptr; }
	
	void execute() const override;
};