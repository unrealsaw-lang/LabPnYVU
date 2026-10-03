#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

class Admin : public Person {
    friend class Course;
    std::vector<Course*> adminCourses;
    std::string department;

public:
    Admin(int id, const std::string& name, const std::string& dept);
    ~Admin() override = default;

    int getManagedCount() const;
    std::string getDepartment() const;

    Admin& operator+=(Course* C);
    Admin& operator-=(Course* C);

    void printInfo() const override;
};