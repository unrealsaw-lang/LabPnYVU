#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include <iostream>

Course::Course(const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max)
    : maxCount(max), level(lvl), language(lang), schedule(sched) {
    if (P != nullptr) addProfessor(P);
}

std::ostream& operator<<(std::ostream& stream, const Course& course) {
    stream << course.getCourseLanguage() << " course";
    stream << "\nLevel: " << course.getCourseLevel();
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
    stream << "\nSchedule: " << course.getCourseSchedule();
    stream << "\nMax capacity: " << course.getCourseMaxCount();
    return stream;
}

std::istream& operator>>(std::istream& stream, Course& course) {
    std::string lang, lvl, sched;
    int max;

    std::cout << "Enter course language: ";
    if (!std::getline(stream, lang) || lang.empty()) {
        std::cout << "Invalid language.\n";
        stream.setstate(std::ios::failbit);
        return stream;
    }
    std::cout << "Enter course level: ";
    if (!std::getline(stream, lvl) || lvl.empty()) {
        std::cout << "Invalid level.\n";
        stream.setstate(std::ios::failbit);
        return stream;
    }
    std::cout << "Enter course schedule: ";
    if (!std::getline(stream, sched) || sched.empty()) {
        std::cout << "Invalid schedule.\n";
        stream.setstate(std::ios::failbit);
        return stream;
    }
    std::cout << "Enter course max capacity: ";
    if (!(stream >> max) || max <= 0) {
        std::cout << "Invalid capacity.\n";
        stream.setstate(std::ios::failbit);
        return stream;
    }
    stream.ignore();

    course.language = lang;
    course.level = lvl;
    course.schedule = sched;
    course.maxCount = max;
    return stream;
}

Course& Course::operator+=(Student* s) {
    if (s == nullptr) { std::cout << "Null\n"; return *this; }
    if (studs.size() >= static_cast<size_t>(maxCount)) {
        std::cout << "Course is full (max " << maxCount << ")!\n";
        return *this;
    }
    for (Student* existing : studs) {
        if (existing == s) { std::cout << "Student already enrolled\n"; return *this; }
    }
    studs.push_back(s);
    s->addCourse(this);
    std::cout << "Student added!\n";
    return *this;
}

Course& Course::operator-=(Student* s) {
    if (s == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i] == s) {
            studs.erase(studs.begin() + static_cast<std::ptrdiff_t>(i));
            s->removeCourse(this);
            std::cout << "Student removed!\n";
            return *this;
        }
    }
    std::cout << "Student not found...\n";
    return *this;
}

Course& Course::operator+=(Professor* p) {
    if (p == nullptr) { std::cout << "Null\n"; return *this; }
    for (Professor* existing : profs) {
        if (existing == p) { std::cout << "Professor already assigned\n"; return *this; }
    }
    profs.push_back(p);
    p->addCourse(this);
    std::cout << "Professor added!\n";
    return *this;
}

Course& Course::operator-=(Professor* p) {
    if (p == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i] == p) {
            profs.erase(profs.begin() + static_cast<std::ptrdiff_t>(i));
            p->removeCourse(this);
            std::cout << "Professor removed!\n";
            return *this;
        }
    }
    std::cout << "Professor not found...\n";
    return *this;
}

void Course::printCourse() const {
    std::cout << "--------------------------------------\n";
    std::cout << language << " course (" << level << ")\n";
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

int Course::addStudent(Student* S) {
    if (S == nullptr || studs.size() >= static_cast<size_t>(maxCount)) return 0;
    for (Student* existing : studs) {
        if (existing == S) return 1;
    }
    studs.push_back(S);
    return 1;
}

int Course::addProfessor(Professor* P) {
    if (P == nullptr) return 0;
    for (Professor* existing : profs) {
        if (existing == P) return 1;
    }
    profs.push_back(P);
    P->addCourse(this);
    return 1;
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

void Course::removeStudent(const Student* S) {
    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i] == S) {
            studs.erase(studs.begin() + static_cast<std::ptrdiff_t>(i));
            break;
        }
    }
}

void Course::removeProfessor(const Professor* P) {
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i] == P) {
            profs.erase(profs.begin() + static_cast<std::ptrdiff_t>(i));
            break;
        }
    }
}