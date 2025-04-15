#pragma once

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

public:
	Form(FormType p_formType) : _formType(p_formType) { (void) _formType; }
	virtual ~Form() {}

	virtual void execute() = 0;
};

class CourseFinishedForm : public Form
{
private:

public:
	void execute();
};

class NeedMoreClassRoomForm : public Form
{
private:

public:
	void execute();
};

class NeedCourseCreationForm : public Form
{
private:

public:
	void execute();
};

class SubscriptionToCourseForm : public Form
{
private:

public:
	void execute();
};