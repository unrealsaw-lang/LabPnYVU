#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Person.h"

class Course;

class Professor : public Person
{
    friend class Course;
    std::string department;
    std::vector<int> feedbacks;

public:
    Professor(int id, const std::string& name, const std::string& dep);
    ~Professor() override = default;

    friend std::ostream& operator<<(std::ostream& stream, const Professor& P);
    friend std::istream& operator>>(std::istream& stream, Professor& P);

    Professor& operator+=(Course* C) override;
    Professor& operator-=(Course* C) override;

    std::string getType() const override;
    std::string getDepartment() const { return department; }

    void rate(int r) { feedbacks.push_back(r); }
    double calculateAverageRating() const;
    void professorRateMenu(Professor* P);

    int calculateWorkload() const override;
    void printInfo() const override;
};