#include "Professor.h"
#include "Course.h"
#include <iostream>

Professor::Professor(int id, const std::string& N) : id(id), name(N) {}

std::ostream& operator<<(std::ostream& stream, const Professor& P) {
    stream << "Professor(id=" << P.id << ") " << P.getName();
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
    stream << "\n";
    return stream;
}
std::istream& operator>>(std::istream& stream, Professor& P) {
    std::cout << "Enter professor name: ";
    std::getline(stream, P.name);
    return stream;
}

Professor& Professor::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    (*C) += this;
    return *this;
}
Professor& Professor::operator-=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    (*C) -= this;
    return *this;
}

void Professor::printInfo() const {
    std::cout << "\n--------------------------------------\n";
    std::cout << "Professor(id=" << id << "): " << name << "\n";
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