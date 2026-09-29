#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "Course.h"
#include "Professor.h"
#include "Student.h"

Course* findCourseById(const std::vector<Course*>& allCourses, int id) {
    for (Course* C : allCourses) {
        if (C->getId() == id) return C;
    }
    return nullptr;
}
Student* findStudentById(const std::vector<Student*>& allStudents, int id) {
    for (Student* S : allStudents) {
        if (S->getId() == id) return S;
    }
    return nullptr;
}
Professor* findProfessorById(const std::vector<Professor*>& allProfs, int id) {
    for (Professor* P : allProfs) {
        if (P->getId() == id) return P;
    }
    return nullptr;
}

Course* findCourseByTitle(const std::vector<Course*>& allCourses) {
    std::string courseTitle;
    std::string courseLevel;

    std::cout << "Enter course language: ";
    std::cin >> courseTitle;

    std::cout << "Enter course level: ";
    std::cin >> courseLevel;

    for (Course* C : allCourses) {
        if (C->getCourseLanguage() == courseTitle && C->getCourseLevel() == courseLevel) {
            return C;
        }
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

std::string promptName(const std::string& prompt) {
    std::cout << prompt;
    std::string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    return name;
}
int promptInt(const std::string& prompt) {
    std::cout << prompt;
    int value;
    std::cin >> value;
    std::cin.ignore();
    return value;
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
void showComparison(int op, const std::string& labelA, const std::string& labelB,
    bool eq, bool ne, bool lt, bool gt, bool le, bool ge) {
    if (op < 1 || op > 6) { std::cout << "Invalid choice\n"; return; }
    static const std::array<const char*, 7> symbols = { "", "==", "!=", "<", ">", "<=", ">=" };
    std::array<bool, 7> results = { false, eq, ne, lt, gt, le, ge };
    std::cout << "\n" << labelA << " " << symbols[op] << " " << labelB
        << " : " << (results[op] ? "TRUE" : "FALSE") << "\n";
}

void createCourse(std::vector<Professor*>& allProfs, std::vector<Course*>& allCourses) {
    int id = promptInt("Enter course id: ");

    std::string language = promptName("Enter course language: ");
    std::string level = promptName("Enter course level: ");
    std::string profName = promptName("Enter course professor name: ");
    std::string schedule = promptName("Enter course schedule: ");
    int maxCap = promptInt("Enter course max capacity: ");

    Professor* prof = findProfessorByName(allProfs, profName);
    if (prof == nullptr) {
        int pid = promptInt("Professor not found. Enter professor id: ");
        prof = new Professor(pid, profName);
        allProfs.push_back(prof);
    }

    auto C = new Course(id, language, level, prof, schedule, maxCap);
    allCourses.push_back(C);
    std::cout << "\nCourse(id=" << id << ") created!\n";
}
void createStudent(std::vector<Student*>& allStudents) {
    int id = promptInt("Enter student id: ");
    std::string name = promptName("Enter student name: ");
    auto S = new Student(id, name);
    allStudents.push_back(S);
    std::cout << "\nStudent(id=" << id << ") created!\n";
}
void createProfessor(std::vector<Professor*>& allProfs) {
    int id = promptInt("Enter professor id: ");
    std::string name = promptName("Enter professor name: ");
    auto P = new Professor(id, name);
    allProfs.push_back(P);
    std::cout << "\nProfessor(id=" << id << ") created!\n";
}
void addStudentToCourse(std::vector<Student*>& allStudents, const std::vector<Course*>& allCourses) {
    std::string name = promptName("Enter student name: ");
    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) { std::cout << "\nCourse not found...\n"; return; }

    Student* S = findStudentByName(allStudents, name);
    if (S == nullptr) {
        int id = promptInt("Student not found. Enter student id: ");
        S = new Student(id, name);
        allStudents.push_back(S);
    }

    *C += S;
    std::cout << "\nStudents on course: " << C->getCourseCurrCount() << "\n";
}
void addProfessorToCourse(std::vector<Professor*>& allProfs, const std::vector<Course*>& allCourses) {
    std::string name = promptName("Enter professor name: ");
    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) { std::cout << "\nCourse not found...\n"; return; }

    Professor* P = findProfessorByName(allProfs, name);
    if (P == nullptr) {
        int id = promptInt("Professor not found. Enter professor id: ");
        P = new Professor(id, name);
        allProfs.push_back(P);
    }
    *C += P;
}

void kickStudent(const std::vector<Course*>& allCourses) {
    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) { std::cout << "\nCourse not found...\n"; return; }

    std::string name = promptName("Enter student name: ");
    Student* S = C->findStudentByName(name);
    if (S != nullptr) {
        *C -= S;
    }
    else {
        std::cout << "\nStudent not found in this course...\n";
    }
}
void removeProfessor(const std::vector<Course*>& allCourses) {
    Course* C = findCourseByTitle(allCourses);
    if (C == nullptr) { std::cout << "\nCourse not found...\n"; return; }

    std::string name = promptName("Enter professor name: ");
    Professor* P = C->findProfessorByName(name);
    if (P != nullptr) {
        *C -= P;
    }
    else {
        std::cout << "\nProfessor not found...\n";
    }
}
void deleteCourse(std::vector<Professor*>& allProfs, std::vector<Student*>& allStuds, std::vector<Course*>& allCourses) {
    Course* delC = findCourseByTitle(allCourses);
    if (delC == nullptr) {
        std::cout << "\nCourse not found...\n";
        return;
    }

    for (Professor* P : allProfs) *P -= delC;
    for (Student* S : allStuds) *S -= delC;
    for (size_t i = 0; i < allCourses.size(); ++i) {
        if (allCourses[i] == delC) {
            delete delC;
            allCourses.erase(allCourses.begin() + static_cast<std::ptrdiff_t>(i));
            break;
        }
    }
    std::cout << "\nCourse deleted!\n";
}

void initData(std::vector<Professor*>& allProfs, std::vector<Student*>& allStuds, std::vector<Course*>& allCourses) {
    auto P1 = new Professor(1, "Smith");
    auto P2 = new Professor(2, "Brown");
    auto P3 = new Professor(3, "Johnson");
    auto P4 = new Professor(4, "Potapenko");

    allProfs.push_back(P1);
    allProfs.push_back(P2);
    allProfs.push_back(P3);
    allProfs.push_back(P4);

    auto C1 = new Course(1, "English", "A1", P1, "Mon 10:00", 30);
    auto C2 = new Course(2, "Deutsche", "A2", P1, "Tue 12:00", 20);
    auto C3 = new Course(3, "Russian", "B1", P2, "Wed 10:00", 10);
    auto C4 = new Course(4, "Deutsche", "C1", P3, "Thu 14:00", 30);
    auto C5 = new Course(5, "English", "B2", P4, "Fri 16:00", 25);
    auto C6 = new Course(6, "English", "A1", P4, "Fri 16:05", 15);

    allCourses.push_back(C1);
    allCourses.push_back(C2);
    allCourses.push_back(C3);
    allCourses.push_back(C4);
    allCourses.push_back(C5);
    allCourses.push_back(C6);

    auto S1 = new Student(2, "Steve");
    auto S2 = new Student(1, "Bob");
    auto S3 = new Student(3, "Steve");
    allStuds.push_back(S1);
    allStuds.push_back(S2);
    allStuds.push_back(S3);

    *S1 += C1;
    *S2 += C1;
    *S2 += C2;
    *S3 += C1;
    *C2 += P2;
}

void courseOperators(const std::vector<Course*>& allCourses) {
    showComparisonMenu();
    int op;
    std::cin >> op;
    if (op == 0) return;

    int id1 = promptInt("Enter course A id: ");
    int id2 = promptInt("Enter course B id: ");

    const Course* A = findCourseById(allCourses, id1);
    const Course* B = findCourseById(allCourses, id2);
    if (!A || !B) { std::cout << "Course not found...\n"; return; }

    showComparison(op,
        "Course(id=" + std::to_string(A->getId()) + ")",
        "Course(id=" + std::to_string(B->getId()) + ")",
        *A == *B, *A != *B, *A < *B, *A > *B, *A <= *B, *A >= *B);
}

void studentOperators(const std::vector<Student*>& allStudents) {
    showComparisonMenu();
    int op;
    std::cin >> op;
    if (op == 0) return;

    int id1 = promptInt("Enter student A id: ");
    int id2 = promptInt("Enter student B id: ");

    const Student* A = findStudentById(allStudents, id1);
    const Student* B = findStudentById(allStudents, id2);
    if (!A || !B) { std::cout << "Student not found...\n"; return; }

    showComparison(op,
        "Student(id=" + std::to_string(A->getId()) + ")",
        "Student(id=" + std::to_string(B->getId()) + ")",
        *A == *B, *A != *B, *A < *B, *A > *B, *A <= *B, *A >= *B);
}

void professorOperators(const std::vector<Professor*>& allProfs) {
    showComparisonMenu();
    int op;
    std::cin >> op;
    if (op == 0) return;

    int id1 = promptInt("Enter professor A id: ");
    int id2 = promptInt("Enter professor B id: ");

    const Professor* A = findProfessorById(allProfs, id1);
    const Professor* B = findProfessorById(allProfs, id2);
    if (!A || !B) { std::cout << "Professor not found...\n"; return; }

    showComparison(op,
        "Professor(id=" + std::to_string(A->getId()) + ")",
        "Professor(id=" + std::to_string(B->getId()) + ")",
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
        std::cout << "\n1. Course\n2. Student\n3. Professor\n";
        std::cin >> t;
        std::cin.ignore();
        if (t == 1) {
            int id = promptInt("\nEnter course id: ");
            Course* C = findCourseById(allCourses, id);
            if (C) std::cout << "Found: " << *C << "\n";
            else std::cout << "Course not found...\n";
        }
        else if (t == 2) {
            int id = promptInt("\nEnter student id: ");
            if (Student* S = findStudentById(allStudents, id))
                std::cout << "Found: " << *S << "\n";
            else std::cout << "Student not found...\n";
        }
        else if (t == 3) {
            int id = promptInt("\nEnter professor id: ");
            if (Professor* P = findProfessorById(allProfs, id))
                std::cout << "Found: " << *P << "\n";
            else std::cout << "Professor not found...\n";
        }
        break;
    }

    case 5: {
        int t;
        std::cout << "\n1. Course\n2. Student\n3. Professor\n> ";
        std::cin >> t;
        std::cin.ignore();
        if (t == 1) {
            int id = promptInt("\nEnter course id: ");
            Course* C = findCourseById(allCourses,id);
            if (!C) return;
            else std::cout << "Found: " << *C << "\n";
            std::cin >> *C;
            if (std::cin) std::cout << "\n" << *C << "\n";
            else { std::cout << "Fail\n"; std::cin.clear(); std::cin.ignore(1000, '\n'); }
        }
        else if (t == 2) {
            int id = promptInt("\nEnter student id: ");
            Student* S = findStudentById(allStudents, id);
            if (!S) { std::cout << "Student not found...\n"; return; }
            else std::cout << "Found: " << *S << "\n";
            std::cin >> *S;
            std::cout << "\n" << *S << "\n";
        }
        else if (t == 3) {
            int id = promptInt("\nEnter professor id: ");
            Professor* P = findProfessorById(allProfs, id);
            if (!P) { std::cout << "Professor not found...\n"; return; }
            else std::cout << "Found: " << *P << "\n";
            std::cin >> *P;
            std::cout << "\n" << *P << "\n";
        }
        break;
    }

    case 6: {
        int id = promptInt("\nEnter course id: ");
        Course* C = findCourseById(allCourses,id);
        if (!C) { std::cout << "Course not found\n"; return; }
        else std::cout << "Found: " << *C << "\n";
        int studid = promptInt("\nEnter student id: ");
        Student* S = findStudentById(allStudents, studid);
        if (!S) {
            std::cout << "\nStudent not found  1 - create new  2 - exit\n";
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            if (choice != 1) return;
            std::string n = promptName("Enter student nme: ");
            S = new Student(studid, n);
            allStudents.push_back(S);
        }
        else std::cout << "Found: " << *S << "\n";
        *C += S;
        std::cout << "Students on course: " << C->getCourseCurrCount() << "\n";
        break;
    }

    case 7: {
        int id = promptInt("\nEnter course id: ");
        Course* C = findCourseById(allCourses,id);
        if (!C) { std::cout << "Course not found\n"; return; }
        else std::cout << "Found: " << *C << "\n";
        int studid = promptInt("\nEnter student id: ");
        Student* S = findStudentById(allStudents, studid);
        if (!S) { std::cout << "Student not found...\n"; return; }
        else std::cout << "Found: " << *S << "\n";
        *C -= S;
        std::cout << "Students on course: " << C->getCourseCurrCount() << "\n";
        break;
    }

    case 0: break;
    default: std::cout << "Invalid choice\n";
    }
}

void printAllCourses(const std::vector<Course*>& allCourses) {
    if (allCourses.empty()) { std::cout << "\nNo courses\n"; return; }
    for (Course* C : allCourses) C->printCourse();
}
void printAllStudents(const std::vector<Student*>& allStudents) {
    if (allStudents.empty()) { std::cout << "\nNo students\n"; return; }
    for (Student* S : allStudents) S->printInfo();
}
void printAllProfessors(const std::vector<Professor*>& allProfs) {
    if (allProfs.empty()) { std::cout << "\nNo professors\n"; return; }
    for (Professor* P : allProfs) P->printInfo();
}
void printStudentById(const std::vector<Student*>& allStudents) {
    int id = promptInt("Enter student id: ");
    if (Student* S = findStudentById(allStudents, id)) S->printInfo();
    else std::cout << "\nStudent not found...\n";
}
void printProfessorById(const std::vector<Professor*>& allProfs) {
    int id = promptInt("Enter professor id: ");
    if (Professor* P = findProfessorById(allProfs, id)) P->printInfo();
    else std::cout << "\nProfessor not found...\n";
}
void printCourseById(const std::vector<Course*>& allCourses) {
    int id = promptInt("Enter course id: ");
    if (Course* C = findCourseById(allCourses, id)) C->printCourse();
    else std::cout << "\nCourse not found...\n";
}

int main() {
    std::vector<Professor*> allProfessors;
    std::vector<Student*> allStudents;
    std::vector<Course*> allCourses;

    initData(allProfessors, allStudents, allCourses);

    int choice;
    do {
        std::cout << "\n1.  Print all courses";
        std::cout << "\n2.  Print all students";
        std::cout << "\n3.  Print all professors";
        std::cout << "\n4.  Print student info";
        std::cout << "\n5.  Print professor info";
        std::cout << "\n6.  Create course";
        std::cout << "\n7.  Create student";
        std::cout << "\n8.  Create professor";
        std::cout << "\n9.  Add student to course";
        std::cout << "\n10. Add professor to course";
        std::cout << "\n11. Remove student from course";
        std::cout << "\n12. Remove professor from course";
        std::cout << "\n13. Delete course";
        std::cout << "\n14. Show operators";
        std::cout << "\n0.  Exit";
        std::cout << "\nYour choice: ";
        if (!(std::cin >> choice)) {
            break;
        }

        switch (choice) {
        case 1:  printAllCourses(allCourses);              break;
        case 2:  printAllStudents(allStudents);            break;
        case 3:  printAllProfessors(allProfessors);        break;
        case 4:  printStudentById(allStudents);          break;
        case 5:  printProfessorById(allProfessors);      break;
        case 6:  createCourse(allProfessors, allCourses);  break;
        case 7:  createStudent(allStudents);               break;
        case 8:  createProfessor(allProfessors);           break;
        case 9:  addStudentToCourse(allStudents, allCourses); break;
        case 10: addProfessorToCourse(allProfessors, allCourses); break;
        case 11: kickStudent(allCourses);                  break;
        case 12: removeProfessor(allCourses);              break;
        case 13: deleteCourse(allProfessors, allStudents, allCourses); break;
        case 14: demonstrateOperators(allCourses, allStudents, allProfessors); break;
        default: break;
        }
    } while (choice != 0);

    for (Course* C : allCourses)       delete C;
    for (Professor* P : allProfessors) delete P;
    for (Student* S : allStudents)     delete S;

    return 0;
}