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
    ~Admin() override {
    std::cout << "\n~Admin() Admin '" << getName() << "' (id = " << getId() << ") deleted: ";
    std::cout << "\nresponsibility: " << responsibility << "\n";
    }


    friend std::ostream& operator<<(std::ostream& stream, const Admin& A);
    friend std::istream& operator>>(std::istream& stream, Admin& A);

    Admin& operator+=(Course* C) override;
    Admin& operator-=(Course* C) override;

    std::string getResponsibility() const;
    std::string getType() const override;

    void calculateDominantLanguage() const;

    int calculateWorkload() const override;
    void printInfo() const override;
};