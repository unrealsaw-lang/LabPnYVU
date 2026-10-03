#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(int id, const std::string& N) : Person(id,N) {}

Student& Student::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    (*C) += this;
    return *this;
}
Student& Student::operator-=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    (*C) -= this;
    return *this;
}

void Student::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Student(id=" << getId() << "): " << getName() << "\n";
    std::cout << "Enrolled in courses (" << getCourseCount() << "): ";
    if (studCourses.empty()) {
        std::cout << "None\n";
        return;
    }
    for (size_t i = 0; i < studCourses.size(); ++i) {
        std::cout << studCourses[i]->getCourseLanguage() << " (" << studCourses[i]->getCourseLevel() << ")";
        if (i != studCourses.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}