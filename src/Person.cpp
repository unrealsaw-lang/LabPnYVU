#include <string>
#include <vector>
#include <iostream>
#include "Person.h"

Person::Person(int id, const std::string& N): id(id), name(N){}

std::ostream& operator<<(std::ostream& stream, const Person& P) {
    stream << "Person(id=" << P.id << ") " << P.name;
    return stream;
}
std::istream& operator>>(std::istream& stream, Person& P) {
    std::cout << "Enter  name: ";
    std::getline(stream, P.name);
    return stream;
} 

Person& Person::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    for (Course* existing : courses) {
        if (existing == C) { std::cout << "Already added\n"; return *this; }
    }
    courses.push_back(C);
    return *this;
}
Person& Person::operator-=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) {
            courses.erase(courses.begin() + i);
            return *this;
        }
    }
    std::cout << "Course not found\n";
    return *this;
}