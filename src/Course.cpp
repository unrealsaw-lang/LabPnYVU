#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include <iostream>

Course::Course(int id, const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max)
    : id(id), maxCount(max), level(lvl), language(lang), schedule(sched) {
    if (P != nullptr) *this += P;
}

std::ostream& operator<<(std::ostream& stream, const Course& course) {
    stream << "Course(id=" << course.getId() << ") "
        << course.getLanguage() << " " << course.getLevel();
    stream << "\nProfessor(s): ";
    if (course.profs.empty()) {
        stream << "None";
    }
    else {
        for (size_t i = 0; i < course.profs.size(); ++i) {
            stream << course.profs[i]->getName();
            if (i != course.profs.size() - 1) stream << ", ";
        }
    }
    stream << "\nSchedule: " << course.getSchedule();
    stream << "\nMax capacity: " << course.getMaxCount();
    return stream;
}
std::istream& operator>>(std::istream& stream, Course& course) {
    std::string lang, lvl, sched;
    int max;

    std::cout << "Enter course language: ";
    if (!std::getline(stream, lang) || lang.empty()) {
        std::cout << "Invalid language\n";
        return stream;
    }
    std::cout << "Enter course level: ";
    if (!std::getline(stream, lvl) || lvl.empty()) {
        std::cout << "Invalid level\n";
        return stream;
    }
    std::cout << "Enter course schedule: ";
    if (!std::getline(stream, sched) || sched.empty()) {
        std::cout << "Invalid schedule\n";
        return stream;
    }
    std::cout << "Enter course max capacity: ";
    if (!(stream >> max) || max <= 0) {
        std::cout << "Invalid capacity\n";
        return stream;
    }
    stream.ignore();

    course.language = lang;
    course.level = lvl;
    course.schedule = sched;
    course.maxCount = max;
    return stream;
}

Course& Course::operator+=(Student* S) {
    if (S == nullptr) { std::cout << "Null\n"; return *this; }
    if (studs.size() >= maxCount) {
        std::cout << "Course is full (max " << maxCount << ")!\n";
        return *this;
    }
    for (Student* existing : studs) {
        if (existing == S) { std::cout << "Student already enrolled\n"; return *this; }
    }
    studs.push_back(S); 
    bool found = false;
    for (Course* C : S->courses) {
        if (C == this) { found = true; break; }
    }
    if (!found) S->courses.push_back(this);

    return *this;
}
Course& Course::operator-=(Student* S) {
    if (S == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i] == S) {
            studs.erase(studs.begin() + i);
            for (size_t j = 0; j < S->courses.size(); ++j) {
                if (S->courses[j] == this) {
                    S->courses.erase(S->courses.begin() + j);
                    break;
                }
            }
            std::cout << "Student removed!\n";
            return *this;
        }
    }
    std::cout << "Student not found...\n";
    return *this;
}

Course& Course::operator+=(Professor* P) {
    if (P == nullptr) { std::cout << "Null\n"; return *this; }
    for (Professor* existing : profs) {
        if (existing == P) { std::cout << "Professor already assigned\n"; return *this; }
    }
    profs.push_back(P);
    bool found = false;
    for (Course* C : P->courses) {
        if (C == this) { found = true; break; }
    }
    if (!found) P->courses.push_back(this);

    return *this;
}
Course& Course::operator-=(Professor* P) {
    if (P == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i] == P) {
            profs.erase(profs.begin() + i);
            for (size_t j = 0; j < P->courses.size(); ++j) {
                if (P->courses[j] == this) {
                    P->courses.erase(P->courses.begin() + j);
                    break;
                }
            }
            std::cout << "Professor removed!\n";
            return *this;
        }
    }
    std::cout << "Professor not found...\n";
    return *this;
}

void Course::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Course (id = " << id << "): " << language << " (" << level << ")\n";
    std::cout << "Professor(s): ";
    if (profs.empty()) {
        std::cout << "None";
    }
    else {
        for (size_t i = 0; i < profs.size(); ++i) {
            std::cout << profs[i]->getName();
            if (i != profs.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\nStudents capacity: " << studs.size() << " / " << maxCount << "\n";
    std::cout << "Schedule: " << schedule << "\n";
}

Student* Course::findStudentByName(const std::string& name) const {
    for (Student* S : studs) {
        if (S->getName() == name) return S;
    }
    return nullptr;
}
Professor* Course::findProfessorByName(const std::string& name) const {
    for (Professor* P : profs) {
        if (P->getName() == name) return P;
    }
    return nullptr;
}