#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"

class Student : public Person
{

    friend class Course;
    std::vector<Course*> studCourses;

public:
    Student(int id, const std::string& name);
    virtual ~Student() = default;

    int getCourseCount() const { return (int)studCourses.size(); }

    friend bool operator<(const Student& a, const Student& b) { return a.getCourseCount() < b.getCourseCount(); }
    friend bool operator>(const Student& a, const Student& b) { return b < a; }
    friend bool operator<=(const Student& a, const Student& b) { return !(b < a); }
    friend bool operator>=(const Student& a, const Student& b) { return !(a < b); }

    Student& operator+=(Course* C);
    Student& operator-=(Course* C);

    std::string getType() const override;
    int getWorkload() const override;
    void printInfo() const override;
};