#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"

class Student : public Person
{
    friend class Course;
    std::string studentNumber;
    std::vector<int> marks;

public:
    Student(int id, const std::string& name, const std::string& sId);
    ~Student() override = default;

    friend std::ostream& operator<<(std::ostream& stream, const Student& S);
    friend std::istream& operator>>(std::istream& stream, Student& S);

    Student& operator+=(Course* C) override;
    Student& operator-=(Course* C) override;

    std::string getType() const override;
    std::string getStudentId() const { return studentNumber; }

    void addMark(int m) { marks.push_back(m); }
    double calculateAverageMark() const;
    void studentMarkInfo(Student* S);

    int calculateWorkload() const override;
    void printInfo() const override;
};