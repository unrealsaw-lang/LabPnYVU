#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

class Admin : public Person {
    friend class Course;
    std::vector<Course*> adminCourses; 
    std::string responsibility;

public:
    Admin(int id, const std::string& name, const std::string& dept);
    ~Admin() override = default;

    std::string getResponsibility() const;

    Admin& operator+=(Course* C);
    Admin& operator-=(Course* C);

    std::string getType() const override;
    int getCount() const override { return (int)adminCourses.size(); };
    int getWorkload() const override;
    void printInfo() const override;

    friend std::istream& operator>>(std::istream& stream, Admin& A);
};