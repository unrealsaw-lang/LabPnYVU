#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(const std::string& N) : name(N) {}

std::ostream& operator<<(std::ostream& stream, const Student& S) {
    stream << "Student " << S.getName();
    stream << "\nEnrolled in " << S.getCourseCount() << " course(s)";
    if (S.courses.empty()) {
        stream << "None\n";
        return;
    }

    stream << S.courses[0]->getCourseLanguage() << " (" << S.courses[0]->getCourseLevel() << ")";
    for (size_t j = 1; j < S.courses.size(); ++j) {
        stream << ", " << S.courses[j]->getCourseLanguage() << " (" << S.courses[j]->getCourseLevel() << ")";
    }
}
std::istream& operator>>(std::istream& stream, Student& S) {
    std::cout << "Enter student name: ";
    std::getline(stream, S.name);
    return stream;
}

bool Student::operator==(const Student& otherStudent) const { return name == otherStudent.name; }
bool Student::operator!=(const Student& otherStudent) const { return !(*this == otherStudent); }
bool Student::operator<(const Student& otherStudent) const { return courses.size() < otherStudent.courses.size(); }
bool Student::operator>(const Student& otherStudent) const { return otherStudent < *this; }
bool Student::operator<=(const Student& otherStudent) const { return !(otherStudent < *this); }
bool Student::operator>=(const Student& otherStudent) const { return !(*this < otherStudent); }

std::string Student::getName() const { return name; }
int Student::getCourseCount() const { return courses.size(); }
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
    for (int j = 0; j < courses.size(); ++j) {
        if (courses[j] == C) {
            courses.erase(courses.begin() + j);
            return;
        }
    }
}

void Student::printInfo() const {
    std::cout << "\n--------------------------------------\n"
        << "Student: " << name << "\n"
        << "Enrolled in courses (" << getCourseCount() << "): ";

    if (courses.empty()) {
        std::cout << "None\n";
        return;
    }

    std::cout << courses[0]->getCourseLanguage() << " (" << courses[0]->getCourseLevel() << ")";
    for (size_t j = 1; j < courses.size(); ++j) {
        std::cout << ", " << courses[j]->getCourseLanguage() << " (" << courses[j]->getCourseLevel() << ")";
    }
    std::cout << "\n";
}
