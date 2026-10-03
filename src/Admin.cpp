#include "Admin.h"
#include "Course.h"
#include <iostream>

Admin::Admin(int id, const std::string& name, const std::string& dept)
    : Person(id, name), department(dept) {
}

Admin& Admin::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    for (Course* existing : adminCourses) {
        if (existing == C) { std::cout << "Already managed\n"; return *this; }
    }
    adminCourses.push_back(C);
    std::cout << "Course added to admin!\n";
    return *this;
}
Admin& Admin::operator-=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < adminCourses.size(); ++i) {
        if (adminCourses[i] == C) {
            adminCourses.erase(adminCourses.begin() + i);
            std::cout << "Course removed from admin!\n";
            return *this;
        }
    }
    std::cout << "Course not found...\n";
    return *this;
}

int Admin::getManagedCount() const { return (int)adminCourses.size(); }
std::string Admin::getDepartment() const { return department; }

void Admin::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Admin(id=" << getId() << "): " << getName()
        << " [dept: " << department << "]\n";
    std::cout << "Manages courses (" << getManagedCount() << "): ";
    if (adminCourses.empty()) {
        std::cout << "None\n";
        return;
    }
    for (size_t i = 0; i < adminCourses.size(); ++i) {
        std::cout << adminCourses[i]->getCourseLanguage()
            << " (" << adminCourses[i]->getCourseLevel() << ")";
        if (i != adminCourses.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}