#include <string>
#include <iostream>
#include "Person.h"
#include "Course.h"

Person::Person(int id, const std::string& N) : id(id), name(N) {}

std::ostream& operator<<(std::ostream& stream, const Person& P) {
    stream << "Person id = " << P.id << " , name: " << P.name << " ";
    return stream;
}

std::istream& operator>>(std::istream& stream, Person& P) {
    std::cout << "Enter  name: ";
    std::getline(stream, P.name);
    return stream;
}

Person& Person::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    if (courses.find(C) != -1) { std::cout << "Already added\n"; return *this; }
    courses.add(C);
    return *this;
}

Person& Person::operator-=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    if (courses.find(C) != -1) courses.remove(C);
    else std::cout << "Course not found\n";
    return *this;
}