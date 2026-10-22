#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Exceptions.h"
#include <iostream>

Course::Course(int id, const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max)
    : id(id), maxCount(max), level(lvl), language(lang), schedule(sched) {
    if (max <= 0) {
        throw invalidDataError("Course size should be > 0");
    }
    if (P == nullptr) {
        throw missingObjectError("Null pointer to Professor object");
    }
    else *this += P;
}

std::ostream& operator<<(std::ostream& stream, const Course& course) {
    stream << "Course(id=" << course.getId() << ") " << course.getLanguage() << " " << course.getLevel();
    stream << "\nProfessor(s): ";
    if (course.profs.getSize() == 0) {
        stream << "None";
    }
    else {
        int idx = 0;
        for (auto prof : course.profs) {
            stream << prof->getName();
            if (++idx < course.profs.getSize()) stream << ", ";
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
    if (!std::getline(stream, lang) || lang.empty()) { std::cout << "Invalid language\n"; return stream; }
    std::cout << "Enter course level: ";
    if (!std::getline(stream, lvl) || lvl.empty()) { std::cout << "Invalid level\n"; return stream; }
    std::cout << "Enter course schedule: ";
    if (!std::getline(stream, sched) || sched.empty()) { std::cout << "Invalid schedule\n"; return stream; }
    std::cout << "Enter course max capacity: ";
    if (!(stream >> max) || max <= 0) { std::cout << "Invalid capacity\n"; return stream; }
    stream.ignore();

    course.language = lang;
    course.level = lvl;
    course.schedule = sched;
    course.maxCount = max;
    return stream;
}

Course& Course::operator+=(Student* S) {
    if (S == nullptr) throw missingObjectError("Null pointer to Student object");
    if (studs.getSize() >= maxCount) throw limitViolationError("Current course limit is " + std::to_string(maxCount));
    if (studs.find(S) != -1) throw invalidOperationError("Student already assigned");

    studs.add(S);
    if (S->courses.find(this) == -1) S->courses.add(this);
    return *this;
}

Course& Course::operator-=(Student* S) {
    if (S == nullptr) throw missingObjectError("Null pointer to Student object");
    if (studs.find(S) != -1) {
        studs.remove(S);
        S->courses.remove(this);
        std::cout << "Student removed!\n";
    }
    else throw missingObjectError("Student is not enrolled in this course");
    return *this;
}

Course& Course::operator+=(Professor* P) {
    if (P == nullptr) throw missingObjectError("Null pointer to Professor object");
    if (profs.find(P) != -1) throw invalidOperationError("Professor already assigned");

    profs.add(P);
    if (P->courses.find(this) == -1) P->courses.add(this);
    return *this;
}

Course& Course::operator-=(Professor* P) {
    if (P == nullptr) throw missingObjectError("Null pointer to Professor object");
    if (profs.find(P) != -1) {
        profs.remove(P);
        P->courses.remove(this);
        std::cout << "Professor removed!\n";
    }
    else throw missingObjectError("Professor is not assigned to this course");
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
        int idx = 0;
        for (auto prof : profs) {
            std::cout << prof->getName();
            if (++idx < profs.getSize()) std::cout << ", ";
        }
    }
    std::cout << "\nStudents capacity: " << studs.getSize() << " / " << maxCount << "\n";
    std::cout << "Schedule: " << schedule << "\n";
}

Student* Course::findStudentByName(const std::string& name) const {
    return studs.findBy([&](const Student* S) { return S->getName() == name; });
}

Professor* Course::findProfessorByName(const std::string& name) const {
    return profs.findBy([&](const Professor* P) { return P->getName() == name; });
}