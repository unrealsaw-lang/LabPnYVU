#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(int id, const std::string& N) : id(id), name(N) {}

std::ostream& operator<<(std::ostream& stream, const Student& S) {
    stream << "Student(id=" << S.id << ") " << S.getName();
    stream << "\nEnrolled in " << S.getCourseCount() << " course(s): ";
    if (S.courses.empty()) {
        stream << "None\n";
        return stream;
    }
    for (size_t i = 0; i < S.courses.size(); ++i) {
        stream << S.courses[i]->getCourseLanguage() << " (" << S.courses[i]->getCourseLevel() << ")";
        if (i != S.courses.size() - 1) stream << ", ";
    }
    stream << "\n";
    return stream;
}
std::istream& operator>>(std::istream& stream, Student& S) {
    std::cout << "Enter student name: ";
    std::getline(stream, S.name);
    return stream;
}

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
    std::cout << "Student(id=" << id << "): " << name << "\n";
    std::cout << "Enrolled in courses (" << getCourseCount() << "): ";
    if (courses.empty()) {
        std::cout << "None\n";
        return;
    }
    for (size_t i = 0; i < courses.size(); ++i) {
        std::cout << courses[i]->getCourseLanguage() << " (" << courses[i]->getCourseLevel() << ")";
        if (i != courses.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}