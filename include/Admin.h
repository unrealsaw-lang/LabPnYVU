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

    int getManagedCount() const;
    std::string getResponsibility() const;

    friend bool operator<(const Admin& a, const Admin& b) { return a.getManagedCount() < b.getManagedCount(); }
    friend bool operator>(const Admin& a, const Admin& b) { return b < a; }
    friend bool operator<=(const Admin& a, const Admin& b) { return !(b < a); }
    friend bool operator>=(const Admin& a, const Admin& b) { return !(a < b); }

    Admin& operator+=(Course* C);
    Admin& operator-=(Course* C);

    std::string getType() const override;
    int getWorkload() const override;
    void printInfo() const override;

    friend std::istream& operator>>(std::istream& stream, Admin& A);
};