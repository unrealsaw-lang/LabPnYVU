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