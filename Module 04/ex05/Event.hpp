#pragma once

enum class Event
{
	RingBell
};

class Observer {
public:
	virtual void update(Event event) = 0;
};

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify(Event event) = 0;
};