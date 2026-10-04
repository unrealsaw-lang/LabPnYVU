#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"

class Course;

class Professor : public Person
{

    friend class Course;
    std::vector<Course*> profCourses;

public:
    Professor(int id, const std::string& name);
    ~Professor() override = default;


    int getCourseCount() const { return (int)profCourses.size(); }

    friend bool operator<(const Professor& a, const Professor& b) { return a.getCourseCount() < b.getCourseCount(); }
    friend bool operator>(const Professor& a, const Professor& b) { return b < a; }
    friend bool operator<=(const Professor& a, const Professor& b) { return !(b < a); }
    friend bool operator>=(const Professor& a, const Professor& b) { return !(a < b); }

    Professor& operator+=(Course* C);
    Professor& operator-=(Course* C);

    std::string getType() const override;
    int getWorkload() const override;
    void printInfo() const override;
};