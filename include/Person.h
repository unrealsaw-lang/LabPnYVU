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

    virtual std::string getType() const = 0;
    virtual int getCount() const = 0;
    virtual int getWorkload() const = 0;
    virtual void printInfo() const = 0;


    friend bool operator==(const Person& A, const Person& B) { return A.id==B.id; }
    friend bool operator!=(const Person& A, const Person& B) { return !(A == B); }
    friend bool operator<(const Person& A, const Person& B) { return A.getCount() < B.getCount(); }
    friend bool operator>(const Person& A, const Person& B) { return B < A; }
    friend bool operator<=(const Person& A, const Person& B) { return !(B < A); }
    friend bool operator>=(const Person& A, const Person& B) { return !(A < B); }
};