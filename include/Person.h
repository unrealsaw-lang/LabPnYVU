#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Course.h"

class Person 
{

    friend class Course;

protected:
    int id;
    std::string name;
    std::vector<Course*> courses;

public:
    Person(int id, const std::string& N);
    virtual ~Person() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }

    void setName(const std::string& N) { name = N; }

    friend std::ostream& operator<<(std::ostream& stream, const Person& S);
    friend std::istream& operator>>(std::istream& stream, Person& S);

    virtual std::string getType() const = 0;
    virtual int getCount() const { return (int)courses.size(); };
    virtual int getWorkload() const = 0;
    virtual void printInfo() const = 0;


    friend std::istream& operator>>(std::istream& stream, Person& P);
    friend std::istream& operator<<(std::istream& stream, Person& P);

    friend bool operator==(const Person& P1, const Person& P2) { return P1.id== P2.id; }
    friend bool operator!=(const Person& P1, const Person& P2) { return !(P1 == P2); }
    friend bool operator<(const Person& P1, const Person& P2) { return P1.getCount() < P2.getCount(); }
    friend bool operator>(const Person& P1, const Person& P2) { return P2 < P1; }
    friend bool operator<=(const Person& P1, const Person& P2) { return !(P2 < P1); }
    friend bool operator>=(const Person& P1, const Person& P2) { return !(P1 < P2); }
};