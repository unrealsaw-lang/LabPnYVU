#include "Admin.h"
#include "Course.h"
#include "Collection.h"
#include <iostream>

Admin::Admin(int id, const std::string& name, const std::string& resp) : Person(id, name), responsibility(resp) {}

std::ostream& operator<<(std::ostream& stream, const Admin& A) {
    stream << "Admin " << A.name << " (";
    stream << static_cast<const Person&>(A) << ", ";
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
int Admin::calculateWorkload() const { return courses.getSize(); }

void Admin::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Admin " << getName() << " (id = " << getId() << ")\n";
    std::cout << "Responsibility: " << responsibility << "\n";
    std::cout << "Manages " << getCount() << " course(s): ";
    if (courses.getSize() == 0) {
        std::cout << "None\n";
        return;
    }
    for (int i = 0; i < courses.getSize(); ++i) {
        std::cout << courses.get(i)->getLanguage()
            << " (" << courses.get(i)->getLevel() << ", course id = " << courses.get(i)->getId() << ")";
        if (i != courses.getSize() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

void Admin::calculateDominantLanguage() const {
    if (courses.getSize() == 0) {
        std::cout << "\nAdmin " << getName() << " manages 0 courses\n";
        return;
    }

    std::cout << "\nAdmin " << getName() << " manages " << courses.getSize() << " course(s):\n";

    collection<std::string> languages;
    collection<int> counts;

    for (int i = 0; i < courses.getSize(); ++i) {
        std::string lang = courses.get(i)->getLanguage();
        int index = languages.find(lang);

        if (index == -1) {
            languages.add(lang);
            counts.add(1);
        }
        else {
            collection<int> tempCounts;
            for (int k = 0; k < counts.getSize(); ++k) {
                if (k == index) tempCounts.add(counts.get(k) + 1);
                else tempCounts.add(counts.get(k));
            }
            counts = tempCounts;
        }
    }

    for (int i = 0; i < languages.getSize(); ++i) {
        double percent = 100.0 * counts.get(i) / courses.getSize();
        std::cout << i + 1 << ") " << languages.get(i) << ": "
            << counts.get(i) << " (" << percent << "%)\n";
    }

    int maxCount = 0;
    for (int i = 0; i < counts.getSize(); ++i) {
        if (counts.get(i) > maxCount) maxCount = counts.get(i);
    }

    collection<std::string> top;
    for (int i = 0; i < languages.getSize(); ++i) {
        if (counts.get(i) == maxCount) top.add(languages.get(i));
    }

    std::cout << "Dominant language: ";
    if (top.getSize() == 1) {
        std::cout << top.get(0) << "\n";
    }
    else {
        for (int i = 0; i < top.getSize(); ++i) {
            std::cout << top.get(i);
            if (i != top.getSize() - 1) std::cout << " and ";
        }
        std::cout << "\n";
    }
}