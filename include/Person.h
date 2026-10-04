#pragma once
#include <string>
#include <vector>
#include <iostream>

class Person {
private:
    int id;
    std::string name;

public:
    Person(int id, const std::string& N);
    virtual ~Person() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }

    void setName(const std::string& N) { name = N; }

    friend std::ostream& operator<<(std::ostream& stream, const Person& S);
    friend std::istream& operator>>(std::istream& stream, Person& S);

    friend bool operator==(const Person& a, const Person& b) { return a.id == b.id; }
    friend bool operator!=(const Person& a, const Person& b) { return !(a == b); }

    virtual std::string getType() const = 0;
    virtual int getWorkload() const = 0;
    virtual void printInfo() const = 0;
};