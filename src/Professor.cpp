#include "Professor.h"
#include "Course.h"
#include <iostream>

Professor::Professor(const std::string& N) : name(N) {}

std::ostream& operator<<(std::ostream& stream, const Professor& P) {
    stream << "Professor " << P.getName();
    stream << "\nCurrently leads: ";

    if (P.courses.empty()) stream << "None";
    else {
        for (size_t i = 0; i < P.courses.size(); ++i) {
            stream << P.courses[i]->getCourseLanguage() << " (" << P.courses[i]->getCourseLevel() << ")";
            if (i != P.courses.size() - 1) stream << ", ";
        }
    }
}

bool Professor::operator==(const Professor& otherProfessor) { return name == otherProfessor.name; }
bool Professor::operator>(const Professor& otherProfessor) { return courses.size() > otherProfessor.courses.size(); }
bool Professor::operator<(const Professor& otherProfessor) { return courses.size() < otherProfessor.courses.size(); }

int Professor::addCourse(Course* C) {
    if (C == nullptr) return 0;
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) return 1;
    }
    courses.push_back(C);
    return 1;
}

void Professor::removeCourse(const Course* C) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == C) {
            courses.erase(courses.begin() + i);
            break;
        }
    }
}

std::string Professor::getName() const { return name; }
int Professor::getCourseCount() const { return courses.size(); }
void Professor::setName(const std::string& N) { name = N; }

void Professor::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Professor: " << name << "\n";
    std::cout << "Leads courses (" << getCourseCount() << "): ";

    if (courses.empty()) std::cout << "None";
    else {
        for (size_t i = 0; i < courses.size(); ++i) {
            std::cout << courses[i]->getCourseLanguage() << " (" << courses[i]->getCourseLevel() << ")";
            if (i != courses.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}