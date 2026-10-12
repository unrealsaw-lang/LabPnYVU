#include "Admin.h"
#include "Course.h"
#include <iostream>

Admin::Admin(int id, const std::string& name, const std::string& resp) : Person(id, name), responsibility(resp) {}

std::ostream& operator<<(std::ostream& stream, const Admin& A) {
    stream << "Admin " << A.name << " (";
    stream << static_cast<const Person&>(A);
    stream << "responsibility: " << A.responsibility << " )";
    return stream;
}
std::istream& operator>>(std::istream& stream, Admin& A) {
    stream >> static_cast<Person&>(A);
    std::cout << "Enter responsibility: ";
    std::getline(stream, A.responsibility);
    return stream;
}

Admin& Admin::operator+=(Course* C) {
    Person::operator+=(C);
    return *this;
}
Admin& Admin::operator-=(Course* C) {
    Person::operator-=(C);
    return *this;
}

std::string Admin::getResponsibility() const { return responsibility; }
std::string Admin::getType() const { return "Admin"; }
int Admin::calculateWorkload() const { return (int)courses.size(); }

void Admin::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Admin " << getName() << " (id = " << getId() << ")\n";
    std::cout << "Responsibility: " << responsibility << "\n";
    std::cout << "Manages " << getCount() << " course(s): ";
    if (courses.empty()) {
        std::cout << "None\n";
        return;
    }
    for (size_t i = 0; i < courses.size(); ++i) {
        std::cout << courses[i]->getCourseLanguage()
            << " (" << courses[i]->getCourseLevel() << ", course id = " << courses[i]->getId() <<")";
        if (i != courses.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

void Admin::calculateDominantLanguage() const {
    if (courses.empty()) {
        std::cout << "\nAdmin " << getName() << " manages 0 courses\n";
        return;
    }

    std::cout << "\nAdmin " << getName() << " manages " << courses.size() << " course(s):\n";

    std::vector<std::string> languages;
    std::vector<int> counts;

    for (Course* c : courses) {
        std::string lang = c->getCourseLanguage();

        int index = -1;
        for (size_t i = 0; i < languages.size(); ++i) {
            if (languages[i] == lang) { index = (int)i; break; }
        }

        if (index == -1) {
            languages.push_back(lang);
            counts.push_back(1);
        }
        else counts[index]++;
    }

    for (size_t i = 0; i < languages.size(); ++i) {
        double percent = 100.0 * counts[i] / courses.size();
        std::cout << i+1 << ") " << languages[i] << ": "
        << counts[i] << " (" << percent << "%)\n";
    }

    int maxCount = 0;
    for (size_t i = 0; i < counts.size(); ++i) {
        if (counts[i] > maxCount) maxCount = counts[i];
    }

    std::vector<std::string> top;
    for (size_t i = 0; i < languages.size(); ++i) {
        if (counts[i] == maxCount) top.push_back(languages[i]);
    }

    std::cout << "Dominant language: ";
    if (top.size() == 1) {
        std::cout << top[0] << "\n";
    }
    else {
        for (size_t i = 0; i < top.size(); ++i) {
            std::cout << top[i];
            if (i != top.size() - 1) std::cout << " and ";
        }
        std::cout << "\n";
    }
}