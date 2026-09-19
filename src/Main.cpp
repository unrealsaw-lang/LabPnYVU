#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Professor.h"
#include "Student.h"

Course* findCourseByTitle(const std::vector<Course*>& allCourses) {
    std::string courseTitle;
    std::string courseLevel;

    std::cout << "Enter course language: ";
    std::cin >> courseTitle;

    std::cout << "Enter course level: ";
    std::cin >> courseLevel;

    for (Course* C : allCourses) {
        if (C->getCourseLanguage() == courseTitle && C->getCourseLevel() == courseLevel)
            return C;
    }
    return nullptr;
}

Student* findStudentByName(const std::vector<Student*>& allStudents, const std::string& name) {
    for (Student* S : allStudents) {
        if (S->getName() == name) return S;
    }
    return nullptr;
}

Professor* findProfessorByName(const std::vector<Professor*>& allProfs, const std::string& name) {
    for (Professor* P : allProfs) {
        if (P->getName() == name) return P;
    }
    return nullptr;
}

Professor* findOrCreateProfessor(std::vector<Professor*>& allProfs, const std::string& name) {
    if (Professor* P = findProfessorByName(allProfs, name)) return P;
    auto newP = new Professor(name);
    allProfs.push_back(newP);
    return newP;
}

Student* findOrCreateStudent(std::vector<Student*>& allStudents, const std::string& name) {
    if (Student* S = findStudentByName(allStudents, name)) return S;
    auto newS = new Student(name);
    allStudents.push_back(newS);
    return newS;
}

std::string promptName(const std::string& prompt) {
    std::cout << prompt;
    std::string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    return name;
}

void showComparisonMenu() {
    std::cout << "\n1. Operator ==\n";
    std::cout << "2. Operator !=\n";
    std::cout << "3. Operator <\n";
    std::cout << "4. Operator >\n";
    std::cout << "5. Operator <=\n";
    std::cout << "6. Operator >=\n";
    std::cout << "0. Back\n";
    std::cout << "Your choice: ";
}

void showComparison(int op,
    const std::string& labelA, const std::string& labelB,
    bool eq, bool ne, bool lt, bool gt, bool le, bool ge) {
    if (op < 1 || op > 6) { std::cout << "Invalid choice\n"; return; }
    static const char* symbols[] = { "", "==", "!=", "<", ">", "<=", ">=" };
    bool results[] = { false, eq, ne, lt, gt, le, ge };
    std::cout << "\n" << labelA << " " << symbols[op] << " " << labelB
        << " : " << (results[op] ? "TRUE" : "FALSE") << "\n";
}

void createCourse(std::vector<Professor*>& allProfs, std::vector<Course*>& allCourses) {
    std::string language;
    std::string level;
    std::string profName;
    std::string schedule;

    int maxCap = 0;

    std::cout << "Enter course language: ";
    std::cin.ignore();
    std::getline(std::cin, language);

    std::cout << "Enter course level: ";
    std::getline(std::cin, level);

    std::cout << "Enter course professor name: ";
    std::getline(std::cin, profName);

    std::cout << "Enter course schedule: ";
    std::getline(std::cin, schedule);

    std::cout << "Enter course max capacity: ";
    std::cin >> maxCap;

    Professor* prof = findOrCreateProfessor(allProfs, profName);
    auto C = new Course(language, level, prof, schedule, maxCap);
    allCourses.push_back(C);

    std::cout << "\nCourse successfully created!\n";
}

void addStudentToCourse(std::vector<Student*>& allStudents, const std::vector<Course*>& allCourses) {
    std::string name = promptName("Enter student name: ");

    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) {
        std::cout << "\nCourse not found...\n";
        return;
    }

    Student* S = findOrCreateStudent(allStudents, name);
    if (S->addCourse(C) == 1) {
        std::cout << "\nStudent " << name << " successfully added to "
            << C->getCourseLanguage() << " (" << C->getCourseLevel() << ")!\n";
    }
    else std::cout << "\nFailed!\n";
}

void addProfessorToCourse(std::vector<Professor*>& allProfs, const std::vector<Course*>& allCourses) {
    std::string name = promptName("Enter professor name: ");

    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) {
        std::cout << "\nCourse not found...\n";
        return;
    }

    Professor* P = findOrCreateProfessor(allProfs, name);
    if (C->addProfessor(P) == 1) std::cout << "\nProfessor " << name << " added successfully!\n";
    else std::cout << "\nFailed!\n";
}

void kickStudent(const std::vector<Course*>& allCourses) {
    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) {
        std::cout << "\nCourse not found...\n";
        return;
    }

    std::string name = promptName("Enter student name: ");

    Student* S = C->findStudentByName(name);
    if (S != nullptr) {
        C->removeStudent(S);
        S->removeCourse(C);
        std::cout << "\nStudent removed from course!\n";
    }
    else std::cout << "\nStudent not found in this course...\n";
}

void removeProfessor(const std::vector<Course*>& allCourses) {
    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) {
        std::cout << "\nCourse not found...\n";
        return;
    }

    std::string name = promptName("Enter professor name: ");

    Professor* P = C->findProfessorByName(name);
    if (P != nullptr) {
        C->removeProfessor(P);
        P->removeCourse(C);
        std::cout << "\nProfessor removed from course!\n";
    }
    else std::cout << "\nProfessor not found...\n";
}

void deleteCourse(std::vector<Professor*>& allProfs, std::vector<Student*>& allStuds, std::vector<Course*>& allCourses) {
    Course* delC = findCourseByTitle(allCourses);
    if (delC == nullptr) {
        std::cout << "\nCourse not found...\n";
        return;
    }

    for (Professor* P : allProfs) P->removeCourse(delC);
    for (Student* S : allStuds) S->removeCourse(delC);
    for (size_t i = 0; i < allCourses.size(); ++i) {
        if (allCourses[i] == delC) {
            delete delC;
            allCourses.erase(allCourses.begin() + i);
            break;
        }
    }
    std::cout << "\nCourse deleted!\n";
}

void initData(std::vector<Professor*>& allProfs, std::vector<Student*>& allStuds, std::vector<Course*>& allCourses) {
    auto P1 = new Professor("Smith");
    auto P2 = new Professor("Brown");
    auto P3 = new Professor("Johnson");
    auto P4 = new Professor("Potapenko");

    allProfs.push_back(P1);
    allProfs.push_back(P2);
    allProfs.push_back(P3);
    allProfs.push_back(P4);

    auto C1 = new Course("English", "A1", P1, "Mon 10:00", 30);
    auto C2 = new Course("Deutsche", "A2", P1, "Tue 12:00", 20);
    auto C3 = new Course("Russian", "B1", P2, "Wed 10:00", 10);
    auto C4 = new Course("Deutsche", "C1", P3, "Thu 14:00", 30);
    auto C5 = new Course("English", "B2", P4, "Fri 16:00", 25);

    allCourses.push_back(C1);
    allCourses.push_back(C2);
    allCourses.push_back(C3);
    allCourses.push_back(C4);
    allCourses.push_back(C5);

    auto S1 = new Student("Steve");
    auto S2 = new Student("Bob");
    allStuds.push_back(S1);
    allStuds.push_back(S2);

    S1->addCourse(C1);
    S2->addCourse(C1);
    S2->addCourse(C2);
    C2->addProfessor(P2);
}

void courseOperators(const std::vector<Course*>& allCourses) {
    showComparisonMenu();
    int op; std::cin >> op;
    if (op == 0) return;

    const Course* A = findCourseByTitle(allCourses);
    if (!A) { std::cout << "Course A not found\n"; return; }
    const Course* B = findCourseByTitle(allCourses);
    if (!B) { std::cout << "Course B not found\n"; return; }

    showComparison(op,
        A->getCourseLanguage() + " " + A->getCourseLevel(),
        B->getCourseLanguage() + " " + B->getCourseLevel(),
        *A == *B, *A != *B, *A < *B, *A > *B, *A <= *B, *A >= *B);
}

void studentOperators(const std::vector<Student*>& allStudents) {
    showComparisonMenu();
    int op; std::cin >> op;
    if (op == 0) return;

    std::string n1 = promptName("Enter student A name: ");
    std::cout << "Enter student B name: ";
    std::string n2; std::getline(std::cin, n2);

    const Student* A = findStudentByName(allStudents, n1);
    const Student* B = findStudentByName(allStudents, n2);
    if (!A || !B) { std::cout << "Student not found...\n"; return; }

    showComparison(op, "Student " + A->getName(), "Student " + B->getName(),
        *A == *B, *A != *B, *A < *B, *A > *B, *A <= *B, *A >= *B);
}

void professorOperators(const std::vector<Professor*>& allProfs) {
    showComparisonMenu();
    int op; std::cin >> op;
    if (op == 0) return;

    std::string n1 = promptName("Enter professor A name: ");
    std::cout << "Enter professor B name: ";
    std::string n2; std::getline(std::cin, n2);

    const Professor* A = findProfessorByName(allProfs, n1);
    const Professor* B = findProfessorByName(allProfs, n2);
    if (!A || !B) { std::cout << "Professor not found...\n"; return; }

    showComparison(op, "Professor " + A->getName(), "Professor " + B->getName(),
        *A == *B, *A != *B, *A < *B, *A > *B, *A <= *B, *A >= *B);
}

void demonstrateOperators(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs) {
    int choice;
    std::cout << "\n1. Course\n";
    std::cout << "2. Student\n";
    std::cout << "3. Professor\n";
    std::cout << "4. Operator <<\n";
    std::cout << "5. Operator >>\n";
    std::cout << "6. Operator +=\n";
    std::cout << "7. Operator -=\n";
    std::cout << "0. Back\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1: courseOperators(allCourses); break;
    case 2: studentOperators(allStudents); break;
    case 3: professorOperators(allProfs); break;

    case 4: {
        int t;
        std::cout << "\n1. Course\n2. Student\n3. Professor\n> ";
        std::cin >> t; std::cin.ignore();
        if (t == 1) {
            Course* C = findCourseByTitle(allCourses);
            if (C) std::cout << "\n" << *C << "\n";
        }
        else if (t == 2) {
            std::string n = promptName("Enter student name: ");
            if (Student* S = findStudentByName(allStudents, n))
                std::cout << "\n" << *S << "\n";
        }
        else if (t == 3) {
            std::string n = promptName("Enter professor name: ");
            if (Professor* P = findProfessorByName(allProfs, n))
                std::cout << "\n" << *P << "\n";
        }
        break;
    }

    case 5: {
        int t;
        std::cout << "\n1. Course\n2. Student\n> ";
        std::cin >> t; std::cin.ignore();
        if (t == 1) {
            Course* C = findCourseByTitle(allCourses);
            if (!C) return;
            std::cin >> *C;
            if (std::cin) std::cout << "\n" << *C << "\n";
            else { std::cout << "Fail!\n"; std::cin.clear(); std::cin.ignore(1000, '\n'); }
        }
        else if (t == 2) {
            std::string n = promptName("Enter student name: ");
            if (Student* S = findStudentByName(allStudents, n)) {
                std::cin >> *S;
                std::cout << "\n" << *S << "\n";
            }
        }
        break;
    }

    case 6: {
        Course* C = findCourseByTitle(allCourses);
        if (!C) { std::cout << "Course not found\n"; return; }
        std::string n = promptName("Enter student name: ");
        *C += findOrCreateStudent(allStudents, n);
        std::cout << "Students on course: " << C->getCourseCurrCount() << "\n";
        break;
    }

    case 7: {
        Course* C = findCourseByTitle(allCourses);
        if (!C) { std::cout << "Course not found!\n"; return; }
        std::string n = promptName("Enter student name: ");
        Student* S = C->findStudentByName(n);
        if (!S) { std::cout << "Student not found...\n"; return; }
        *C -= S;
        std::cout << "Students on course: " << C->getCourseCurrCount() << "\n";
        break;
    }

    case 0: break;
    default: std::cout << "Invalid choice\n";
    }
}

void printAllCourses(const std::vector<Course*>& allCourses) {
    for (Course* C : allCourses) C->printCourse();
}

void printStudentByName(const std::vector<Student*>& allStudents) {
    std::string name = promptName("Enter student name: ");
    if (Student* S = findStudentByName(allStudents, name)) S->printInfo();
    else std::cout << "\nStudent not found...\n";
}

void printProfessorByName(const std::vector<Professor*>& allProfs) {
    std::string name = promptName("Enter professor name: ");
    if (Professor* P = findProfessorByName(allProfs, name)) P->printInfo();
    else std::cout << "\nProfessor not found...\n";
}

int main() {
    std::vector<Professor*> allProfessors;
    std::vector<Student*> allStudents;
    std::vector<Course*> allCourses;

    initData(allProfessors, allStudents, allCourses);

    int choice;
    do {
        std::cout << "\n1. Print all courses";
        std::cout << "\n2. Print student info";
        std::cout << "\n3. Print professor info";
        std::cout << "\n4. Add course";
        std::cout << "\n5. Add student to course";
        std::cout << "\n6. Add professor to course";
        std::cout << "\n7. Remove student from course";
        std::cout << "\n8. Remove professor from course";
        std::cout << "\n9. Delete course";
        std::cout << "\n10. Show operators";
        std::cout << "\n0. Exit";
        std::cout << "\nYour choice: ";
        if (!(std::cin >> choice)) {
            break;
        }

        switch (choice) {
        case 1: printAllCourses(allCourses); break;
        case 2: printStudentByName(allStudents); break;
        case 3: printProfessorByName(allProfessors); break;
        case 4: createCourse(allProfessors, allCourses); break;
        case 5: addStudentToCourse(allStudents, allCourses); break;
        case 6: addProfessorToCourse(allProfessors, allCourses); break;
        case 7: kickStudent(allCourses); break;
        case 8: removeProfessor(allCourses); break;
        case 9: deleteCourse(allProfessors, allStudents, allCourses); break;
        case 10: demonstrateOperators(allCourses, allStudents, allProfessors); break;
        default: break;
        }
    } while (choice != 0);

    for (Course* C : allCourses)       delete C;
    for (Professor* P : allProfessors) delete P;
    for (Student* S : allStudents)     delete S;

    return 0;
}