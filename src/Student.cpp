#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(const std::string& N) : name(N) {}

std::ostream& operator<<(std::ostream& stream, const Student& S) {
    stream << "Student " << S.getName();
    stream << "\nEnrolled in " << S.getCourseCount() << " course(s): ";
    if (S.courses.empty()) {
        stream << "None\n";
        return stream;
    }
    for (size_t i = 0; i < S.courses.size(); ++i) {
        stream << S.courses[i]->getCourseLanguage() << " (" << S.courses[i]->getCourseLevel() << ")";
        if (i != S.courses.size() - 1) stream << ", ";
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Student& S) {
    std::cout << "Enter student name: ";
    std::getline(stream, S.name);
    return stream;
}

Student& Student::operator+=(Course* c) {
    if (c == nullptr) { std::cout << "Null\n"; return *this; }
    if (courses.size() >= 10) { std::cout << "Student can't take more than 10 courses\n"; return *this; }
    for (Course* existing : courses) {
        if (existing == c) { std::cout << "Already enrolled\n"; return *this; }
    }
    if (c->addStudent(this) == 0) { std::cout << "Course is full\n"; return *this; }
    courses.push_back(c);
    std::cout << "Course added!\n";
    return *this;
}

Student& Student::operator-=(Course* c) {
    if (c == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == c) {
            courses.erase(courses.begin() + static_cast<std::ptrdiff_t>(i));
            c->removeStudent(this);
            std::cout << "Course removed!\n";
            return *this;
        }
    }
    std::cout << "Course not found...\n";
    return *this;
}

int Student::addCourse(Course* C) {
    if (C == nullptr) return 0;
    for (Course* existing : courses) {
        if (existing == C) return 1;
    }
    if (C->addStudent(this) == 0) return 0;
    courses.push_back(C);
    return 1;
}

void Student::removeCourse(const Course* C) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) {
            courses.erase(courses.begin() + static_cast<std::ptrdiff_t>(i));
            return;
        }
    }
}

void Student::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Student: " << name << "\n";
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