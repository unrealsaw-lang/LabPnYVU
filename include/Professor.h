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

    Professor& operator+=(Course* C);
    Professor& operator-=(Course* C);

    std::string getType() const override;
    int getCount() const override { return (int)profCourses.size(); };
    int getWorkload() const override;
    void printInfo() const override;
};