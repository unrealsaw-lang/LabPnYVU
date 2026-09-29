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
        << course.getCourseLanguage() << " " << course.getCourseLevel();
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

Course& Course::operator+=(Student* s) {
    if (s == nullptr) { std::cout << "Null\n"; return *this; }
    if (studs.size() >= maxCount) {
        std::cout << "Course is full (max " << maxCount << ")!\n";
        return *this;
    }
    for (Student* existing : studs) {
        if (existing == s) { std::cout << "Student already enrolled\n"; return *this; }
    }
    studs.push_back(s);
    s->courses.push_back(this);
    return *this;
}
Course& Course::operator-=(Student* s) {
    if (s == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i] == s) {
            studs.erase(studs.begin() + i);
            for (size_t j = 0; j < s->courses.size(); ++j) {
                if (s->courses[j] == this) {
                    s->courses.erase(s->courses.begin() + j);
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

Course& Course::operator+=(Professor* p) {
    if (p == nullptr) { std::cout << "Null\n"; return *this; }
    for (Professor* existing : profs) {
        if (existing == p) { std::cout << "Professor already assigned\n"; return *this; }
    }
    profs.push_back(p);
    p->courses.push_back(this);
    return *this;
}
Course& Course::operator-=(Professor* p) {
    if (p == nullptr) { std::cout << "Null\n"; return *this; }
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i] == p) {
            profs.erase(profs.begin() + i);
            for (size_t j = 0; j < p->courses.size(); ++j) {
                if (p->courses[j] == this) {
                    p->courses.erase(p->courses.begin() + j);
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

void Course::printCourse() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Course(id=" << id << "): " << language << " (" << level << ")\n";
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