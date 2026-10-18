#include "Professor.h"
#include "Course.h"
#include "Menu.h"

Professor::Professor(int id, const std::string& N, const std::string& dep) : Person(id,N), department(dep) {}

std::ostream& operator<<(std::ostream& stream, const Professor& P) {
    stream << "Professor " << P.name << " (";
    stream << static_cast<const Person&>(P);
    stream << "department: " << P.department << " )";
    return stream;
}
std::istream& operator>>(std::istream& stream, Professor& P) {
    stream >> static_cast<Person&>(P);
    std::cout << "Enter department: ";
    std::getline(stream, P.department);
    return stream;
}

Professor& Professor::operator+=(Course* C) {
    if (C == nullptr) { std::cout << "Null\n"; return *this; }
    (*C) += this;
    return *this;
}
Professor& Professor::operator-=(Course* C) {
    Person::operator-=(C);
    (*C) -= this;
    return *this;
}

std::string Professor::getType() const { return "Professor"; }
int Professor::calculateWorkload() const { return (int)courses.size() * 4; }

void Professor::printInfo() const {
    std::cout << "--------------------------------------\n";
    std::cout << "Professor " << getName() << " (id = " << getId() << ", department: " << department << ")\n";
    std::cout << "Leads " << getCount() << " course(s): ";
    if (courses.empty()) {
        std::cout << "None";
    }
    else {
        for (size_t i = 0; i < courses.size(); ++i) {
            std::cout << courses[i]->getLanguage() << " (" << courses[i]->getLevel() << ", course id = " << courses[i]->getId() << ")";
            if (i != courses.size() - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

double Professor::calculateAverageRating() const {
if (feedbacks.empty()) return 0.0;
double avg = 0.0;
for (int i = 0; i < (int)feedbacks.size(); i++) avg += feedbacks[i];
avg /= (int)feedbacks.size();
return avg;
}
void Professor::professorRateMenu(Professor* P) {
    int r; std::cout << "Enter rate: ";
    std::cin >> r;
    P->rate(r);
    std::cout << "Success!";
    std::cout << "\nCurrent professor " << P->getName() << " (id = " << P->getId() << ")";
    std::cout << "\nAverage rating : " << P->calculateAverageRating();
}