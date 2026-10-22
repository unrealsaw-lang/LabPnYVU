#include "Professor.h"
#include "Course.h"
#include "Exceptions.h"
#include "Menu.h"

Professor::Professor(int id, const std::string& N, const std::string& dep) : Person(id, N), department(dep) {}

std::ostream& operator<<(std::ostream& stream, const Professor& P) {
    stream << "Professor " << P.name << " (" << static_cast<const Person&>(P) << ", department: " << P.department << " )";
    return stream;
}

std::istream& operator>>(std::istream& stream, Professor& P) {
    stream >> static_cast<Person&>(P);
    std::cout << "Enter department: ";
    std::getline(stream, P.department);
    return stream;
}

Professor& Professor::operator+=(Course* C) {
    if (C == nullptr) throw missingObjectError("Null pointer to Course object");
    (*C) += this;
    return *this;
}

Professor& Professor::operator-=(Course* C) {
    Person::operator-=(C);
    (*C) -= this;
    return *this;
}

std::string Professor::getType() const { return "Professor"; }
int Professor::calculateWorkload() const { return courses.getSize() * 4; }

void Professor::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Professor " << getName() << " (id = " << getId() << ", department: " << department << ")\n";
    std::cout << "Leads " << getCount() << " course(s): ";
    if (courses.getSize() == 0) {
        std::cout << "None";
    }
    else {
        int idx = 0;
        for (auto crs : courses) {
            std::cout << crs->getLanguage() << " (" << crs->getLevel() << ", course id = " << crs->getId() << ")";
            if (++idx < courses.getSize()) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

double Professor::calculateAverageRating() const {
    if (feedbacks.empty()) throw missingObjectError("Professor does not have any feedbacks");
    double avg = 0.0;
    for (auto f : feedbacks) avg += f;
    return avg / feedbacks.size();
}

void Professor::professorRateMenu(Professor* P) {
    int r; std::cout << "Enter rate: ";
    std::cin >> r;
    P->rate(r);
    std::cout << "\nSuccess!\n";
    std::cout << "\nCurrent professor " << P->getName() << " (id = " << P->getId() << ")";
    std::cout << "\nAverage rating : " << P->calculateAverageRating();
}