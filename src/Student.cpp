#include "Student.h"
#include "Course.h"
#include "Exceptions.h"
#include "Menu.h"

Student::Student(int id, const std::string& N, const std::string& sId) : Person(id, N), studentNumber(sId) {}

std::ostream& operator<<(std::ostream& stream, const Student& S) {
    stream << "Student " << S.name << " (" << static_cast<const Person&>(S) << ", student id = " << S.studentNumber << ")";
    return stream;
}

std::istream& operator>>(std::istream& stream, Student& S) {
    stream >> static_cast<Person&>(S);
    std::cout << "Enter student id: ";
    std::getline(stream, S.studentNumber);
    return stream;
}

Student& Student::operator+=(Course* C) {
    if (C == nullptr) throw missingObjectError("Null pointer to Course object");
    (*C) += this;
    return *this;
}

Student& Student::operator-=(Course* C) {
    Person::operator-=(C);
    (*C) -= this;
    return *this;
}

std::string Student::getType() const { return "Student"; }
int Student::calculateWorkload() const { return courses.getSize() * 2; }

double Student::calculateAverageMark() const {
    if (marks.empty()) throw missingObjectError("Student does not have any marks");
    double avg = 0.0;
    for (auto m : marks) avg += m;
    return avg / marks.size();
}

void Student::studentMarkInfo(Student* S) {
    int mark; std::cout << "Enter mark: ";
    std::cin >> mark;
    S->addMark(mark);
    std::cout << "\nSuccess!\n";
    std::cout << "\nCurrent student " << S->getName() << " (id = " << S->getId() << ") marks: ";
    int idx = 0;
    for (auto m : marks) {
        std::cout << m;
        if (++idx < marks.size()) std::cout << ", ";
    }
    std::cout << "\nAverage mark: " << S->calculateAverageMark();
}

void Student::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Student " << getName() << " (id = " << getId() << ", student id = " << studentNumber << ")\n";
    std::cout << "Enrolled in " << getCount() << " course(s): ";
    if (courses.getSize() == 0) {
        std::cout << "None\n";
        return;
    }
    int idx = 0;
    for (auto crs : courses) {
        std::cout << crs->getLanguage() << " (" << crs->getLevel() << ", course id = " << crs->getId() << ")";
        if (++idx < courses.getSize()) std::cout << ", ";
    }
    std::cout << "\n";
}