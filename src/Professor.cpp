#include "Professor.h"
#include "Course.h"
#include <iostream>

Professor::Professor(const std::string& N) : name(N) {}

std::ostream& operator<<(std::ostream& stream, const Professor& P) {
    stream << "Professor " << P.getName();
    stream << "\nCurrently leads: ";
    if (P.courses.empty()) {
        stream << "None";
    }
    else {
        for (size_t i = 0; i < P.courses.size(); ++i) {
            stream << P.courses[i]->getCourseLanguage() << " (" << P.courses[i]->getCourseLevel() << ")";
            if (i != P.courses.size() - 1) stream << ", ";
        }
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Professor& P) {
    std::cout << "Enter professor name: ";
    std::getline(stream, P.name);
    return stream;
}

Professor& Professor::operator+=(Course* c) {
    if (c == nullptr) { std::cout << "Null\n"; return *this; }
    if (courses.size() >= 10) { std::cout << "Professor can't lead more than 10 courses\n"; return *this; }
    for (Course* existing : courses) {
        if (existing == c) { std::cout << "Course already assigned\n"; return *this; }
    }
    courses.push_back(c);
    c->addProfessor(this);
    std::cout << "Course added!\n";
    return *this;
}

Professor& Professor::operator-=(Course* c) {
    if (c == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == c) {
            courses.erase(courses.begin() + static_cast<std::ptrdiff_t>(i));
            c->removeProfessor(this);
            std::cout << "Course removed!\n";
            return *this;
        }
    }
    std::cout << "Course not found...\n";
    return *this;
}

int Professor::addCourse(Course* C) {
    if (C == nullptr) return 0;
    for (Course* existing : courses) {
        if (existing == C) return 1;
    }
    courses.push_back(C);
    return 1;
}

void Professor::removeCourse(const Course* C) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) {
            courses.erase(courses.begin() + static_cast<std::ptrdiff_t>(i));
            break;
        }
    }
}

void Professor::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Professor: " << name << "\n";
    std::cout << "Leads courses (" << getCourseCount() << "): ";
    if (courses.empty()) {
        std::cout << "None";
    }
    else {
        for (size_t i = 0; i < courses.size(); ++i) {
            std::cout << courses[i]->getCourseLanguage() << " (" << courses[i]->getCourseLevel() << ")";
            if (i != courses.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}