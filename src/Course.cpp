#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include <iostream>

Course::Course(const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max) :
    maxCount(max), currCount(0), level(lvl), language(lang), schedule(sched) {
    if (P != nullptr) addProfessor(P);
}

std::string Course::getCourseLevel() const { return level; }
std::string Course::getCourseLanguage() const { return language; }
std::string Course::getCourseSchedule() const { return schedule; }
int Course::getCourseCurrCount() const { return currCount; }
int Course::getCourseMaxCount() const { return maxCount; }

void Course::setCourseSchedule(const std::string& schd) { schedule = schd; }
void Course::setCourseLanguage(const std::string& lang) { language = lang; }
void Course::setCourseLevel(const std::string& lvl) { level = lvl; }
void Course::setCourseCount(int count) { currCount = count; }

void Course::printCourse() const {
    std::cout << "--------------------------------------\n";
    std::cout << language << " course (" << level << ")\n";
    std::cout << "Professor(s): ";

    if (profs.empty()) std::cout << "None";
    else {
        for (size_t i = 0; i < profs.size(); ++i) {
            std::cout << profs[i]->getName();
            if (i != profs.size() - 1) std::cout << ", ";
        }
    }

    std::cout << "\nStudents capacity: " << currCount << " / " << maxCount << "\n";
    std::cout << "Schedule: " << schedule << "\n";
}

int Course::addStudent(Student* S) {
    if (S == nullptr || currCount >= maxCount) return 0;

    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i] == S) return 1;
    }
    studs.push_back(S);
    currCount++;
    return 1;
}
int Course::addProfessor(Professor* P) {
    if (P == nullptr) return 0;
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i] == P) return 1;
    }
    profs.push_back(P);
    P->addCourse(this);
    return 1;
}

Student* Course::findStudentByName(const std::string& name) const {
    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i]->getName() == name) return studs[i];
    }
    return nullptr;
}
Professor* Course::findProfessorByName(const std::string& name) const {
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i]->getName() == name) return profs[i];
    }
    return nullptr;
}

void Course::removeStudent(const Student* S) {
    for (size_t i = 0; i < studs.size(); ++i) {
        if (studs[i] == S) {
            studs.erase(studs.begin() + i);
            currCount--;
            break;
        }
    }
}
void Course::removeProfessor(const Professor* P) {
    for (size_t i = 0; i < profs.size(); ++i) {
        if (profs[i] == P) {
            profs.erase(profs.begin() + i);
            break;
        }
    }
}