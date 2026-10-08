#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"

class Student : public Person
{
    friend class Course;
    std::string studentId;

public:
    Student(int id, const std::string& name, const std::string& sId);
    ~Student() override = default;

    friend std::ostream& operator<<(std::ostream& stream, const Student& S);
    friend std::istream& operator>>(std::istream& stream, Student& S);

    Student& operator+=(Course* C);
    Student& operator-=(Course* C);

    std::string getType() const override; 
    std::string getStudentId() const { return studentId; }
    int getWorkload() const override;
    void printInfo() const override;

};