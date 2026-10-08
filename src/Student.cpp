#include "Student.h"
#include "Course.h"
#include <iostream>

Student::Student(int id, const std::string& N, const std::string& sId) : Person(id,N), studentId(sId) {}

std::ostream& operator<<(std::ostream& stream, const Student& S) {
    stream << "Student " << S.name << " (";
    stream << static_cast<const Person&>(S);
    stream << "student id = " << S.studentId << ")";
    return stream;
}
std::istream& operator>>(std::istream& stream, Student& S) {
    stream >> static_cast<Person&>(S);
    std::cout << "Enter student id: ";
    std::getline(stream, S.studentId);
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

std::string Student::getType() const { return "Student"; }
int Student::getWorkload() const { return (int)courses.size() * 2; }

void Student::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Student " << getName() << " (id = " << getId() << ", student id = " << studentId << ")\n";
    std::cout << "Enrolled in " << getCount() << " course(s): ";
    if (courses.empty()) {
        std::cout << "None\n";
        return;
    }
    for (size_t i = 0; i < courses.size(); ++i) {
        std::cout << courses[i]->getCourseLanguage() << " (" << courses[i]->getCourseLevel() << ", course id = " << courses[i]->getId() <<")";
        if (i != courses.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}