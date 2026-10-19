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
    if (course.profs.getSize() == 0) {
        stream << "None";
    }
    else {
        for (int i = 0; i < course.profs.getSize(); ++i) {
            stream << course.profs.get(i)->getName();
            if (i != course.profs.getSize() - 1) stream << ", ";
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
    if (studs.getSize() >= maxCount) {
        std::cout << "Course is full (max " << maxCount << ")!\n";
        return *this;
    }
    if (studs.find(S) != -1) {
        std::cout << "Student already enrolled\n";
        return *this;
    }

    studs.add(S);
    if (S->courses.find(this) == -1) S->courses.add(this);

    return *this;
}

Course& Course::operator-=(Student* S) {
    if (S == nullptr) { std::cout << "Null\n"; return *this; }
    if (studs.find(S) != -1) {
        studs.remove(S);
        S->courses.remove(this);
        std::cout << "Student removed!\n";
    }
    else {
        std::cout << "Student not found...\n";
    }
    return *this;
}

Course& Course::operator+=(Professor* P) {
    if (P == nullptr) { std::cout << "Null\n"; return *this; }
    if (profs.find(P) != -1) {
        std::cout << "Professor already assigned\n";
        return *this;
    }

    profs.add(P);
    if (P->courses.find(this) == -1) P->courses.add(this);

    return *this;
}

Course& Course::operator-=(Professor* P) {
    if (P == nullptr) { std::cout << "Null\n"; return *this; }
    if (profs.find(P) != -1) {
        profs.remove(P);
        P->courses.remove(this);
        std::cout << "Professor removed!\n";
    }
    else {
        std::cout << "Professor not found...\n";
    }
    return *this;
}

void Course::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Course (id = " << id << "): " << language << " (" << level << ")\n";
    std::cout << "Professor(s): ";
    if (profs.getSize() == 0) {
        std::cout << "None";
    }
    else {
        for (int i = 0; i < profs.getSize(); ++i) {
            std::cout << profs.get(i)->getName();
            if (i != profs.getSize() - 1) std::cout << ", ";
        }
    }
    std::cout << "\nStudents capacity: " << studs.getSize() << " / " << maxCount << "\n";
    std::cout << "Schedule: " << schedule << "\n";
}

Student* Course::findStudentByName(const std::string& name) const {
    return studs.findBy([&](Student* S) { return S->getName() == name; });
}

Professor* Course::findProfessorByName(const std::string& name) const {
    return profs.findBy([&](Professor* P) { return P->getName() == name; });
}