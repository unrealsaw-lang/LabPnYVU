#include "Professor.h"
#include "Course.h"
#include <iostream>

Professor::Professor(int id, const std::string& N) : Person(id,N) {}

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
    std::cout << "Professor(id=" << getId() << "): " << getName() << "\n";
    std::cout << "Leads courses (" << getCourseCount() << "): ";
    if (profCourses.empty()) {
        std::cout << "None";
    }
    else {
        for (size_t i = 0; i < profCourses.size(); ++i) {
            std::cout << profCourses[i]->getCourseLanguage() << " (" << profCourses[i]->getCourseLevel() << ")";
            if (i != profCourses.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}