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

    Student& operator+=(Course* C);
    Student& operator-=(Course* C);

    std::string getType() const override;
    int getCount() const override { return (int)studCourses.size(); };
    int getWorkload() const override;
    void printInfo() const override;
};