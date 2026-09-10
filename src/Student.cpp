#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(const std::string& N) : name(N) {}

std::string Student::getName() const { return name; }
int Student::getCourseCount() const { return static_cast<int>(courses.size()); }
void Student::setName(const std::string& N) { name = N; }

int Student::addCourse(Course* C) {
    if (C == nullptr) return 0;
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) return 1;
    }
    if (C->addStudent(this) == 0) return 0;

    courses.push_back(C);
    return 1;
}

void Student::removeCourse(const Course* C) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) {
            courses.erase(courses.begin() + i);
            break;
        }
    }
}

void Student::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Student: " << name << "\n";
    std::cout << "In courses (" << getCourseCount() << "): ";

    if (courses.empty()) std::cout << "None";
    else {
        for (size_t i = 0; i < courses.size(); ++i) {
            std::cout << courses[i]->getCourseLanguage() << " (" << courses[i]->getCourseLevel() << ")";
            if (i != courses.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}