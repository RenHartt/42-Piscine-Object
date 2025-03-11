#pragma once

#include <list>
#include <memory>
#include <mutex>

#include "Singleton.hpp"

class Student;
class Staff;
class Course;
class Room;

template <typename T>
class List {
protected:
    std::list<T*> list;
    std::mutex mtx;

public:
    void addList(T* toAdd) {
        std::lock_guard<std::mutex> lock(mtx);
        list.push_back(toAdd);
    }

    std::list<T*> getList() const {
        return list;
    }

    virtual ~List() {}
};

class StudentList : public List<Student>, public Singleton<StudentList> {};
class StaffList : public List<Staff>, public Singleton<StaffList> {};
class CourseList : public List<Course>, public Singleton<CourseList> {};
class RoomList : public List<Room>, public Singleton<RoomList> {};
