#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

class Admin : public Person 
{
    friend class Course; 
    std::string responsibility;

public:
    Admin(int id, const std::string& name, const std::string& resp);
    ~Admin() override = default;


    friend std::ostream& operator<<(std::ostream& stream, const Admin& A);
    friend std::istream& operator>>(std::istream& stream, Admin& A);

    Admin& operator+=(Course* C);
    Admin& operator-=(Course* C);

    std::string getResponsibility() const;
    std::string getType() const override;
    int getWorkload() const override;
    void printInfo() const override;
};