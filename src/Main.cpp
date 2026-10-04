#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include "Menu.h"

void initData(std::vector<Professor*>& allProfs, std::vector<Student*>& allStuds, std::vector<Course*>& allCourses, std::vector<Admin*>& allAdmins) {
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

    auto S1 = new Student(1, "Steve");
    auto S2 = new Student(2, "Bob");
    auto S3 = new Student(3, "Alice");
    auto S4 = new Student(4, "Steve");
    allStuds.push_back(S1);
    allStuds.push_back(S2);
    allStuds.push_back(S3);
    allStuds.push_back(S4);

    *S1 += C1;
    *S2 += C1;
    *S2 += C2;
    *S3 += C3;
    *S4 += C5;
    *C2 += P2;

    auto A1 = new Admin(100, "Anna", "Admissions");
    auto A2 = new Admin(101, "Igor", "Scheduling");
    allAdmins.push_back(A1);
    allAdmins.push_back(A2);

    *A1 += C1;
    *A2 += C3;
}

int main() {
    std::vector<Professor*> allProfessors;
    std::vector<Student*> allStudents;
    std::vector<Course*> allCourses;
    std::vector<Admin*> allAdmins;

    initData(allProfessors, allStudents, allCourses, allAdmins);

    while (true) {
        std::cout << "\n1. Operators\n";
        std::cout << "2. Inheritance\n";
        std::cout << "3. Print\n";
        std::cout << "4. Create\n";
        std::cout << "5. Delete\n";
        std::cout << "0. Exit\n";
        int choice = promptInt("Your choice: ");
        if (choice == 0) break;

        if (choice == 1) operatorsMenu(allCourses, allStudents, allProfessors, allAdmins);
        else if (choice == 2) inheritanceMenu(allCourses, allStudents, allProfessors, allAdmins);
        else if (choice == 3) printMenu(allCourses, allStudents, allProfessors, allAdmins);
        else if (choice == 4) createMenu(allCourses, allStudents, allProfessors, allAdmins);
        else if (choice == 5) deleteMenu(allCourses, allStudents, allProfessors, allAdmins);
        else std::cout << "Invalid\n";
    }

    for (Course* C : allCourses)       delete C;
    for (Professor* P : allProfessors) delete P;
    for (Student* S : allStudents)     delete S;
    for (Admin* A : allAdmins)         delete A;

    return 0;
}