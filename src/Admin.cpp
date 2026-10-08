#include "Admin.h"
#include "Course.h"
#include <iostream>

Admin::Admin(int id, const std::string& name, const std::string& resp) : Person(id, name), responsibility(resp) {}

std::ostream& operator<<(std::ostream& stream, const Admin& A) {
    stream << "Admin " << A.name << " (";
    stream << static_cast<const Person&>(A);
    stream << "responsibility: " << A.responsibility << " )";
    return stream;
}
std::istream& operator>>(std::istream& stream, Admin& A) {
    stream >> static_cast<Person&>(A);
    std::cout << "Enter responsibility: ";
    std::getline(stream, A.responsibility);
    return stream;
}

Admin& Admin::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    for (Course* existing : courses) {
        if (existing == C) { std::cout << "Already managed\n"; return *this; }
    }
    courses.push_back(C);
    return *this;
}
Admin& Admin::operator-=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) {
            courses.erase(courses.begin() + i);
            std::cout << "Course removed from admin!\n";
            return *this;
        }
    }
    std::cout << "Course not found...\n";
    return *this;
}

std::string Admin::getResponsibility() const { return responsibility; }
std::string Admin::getType() const { return "Admin"; }
int Admin::getWorkload() const { return (int)courses.size(); }

void Admin::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Admin " << getName() << " (id = " << getId() << ")\n";
    std::cout << "Responsibility: " << responsibility << "\n";
    std::cout << "Manages " << getCount() << " course(s): ";
    if (courses.empty()) {
        std::cout << "None\n";
        return;
    }
    for (size_t i = 0; i < courses.size(); ++i) {
        std::cout << courses[i]->getCourseLanguage()
            << " (" << courses[i]->getCourseLevel() << ", course id = " << courses[i]->getId() <<")";
        if (i != courses.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}