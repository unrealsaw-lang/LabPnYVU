#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include "Collection.h"
#include "Menu.h"

void initCollectionData(collection<Professor*>& allProfs, collection<Student*>& allStuds, collection<Course*>& allCourses, collection<Admin*>& allAdmins) {
    auto P1 = new Professor(11, "Prof11", "Foreign");
    auto P2 = new Professor(12, "Prof12", "Native");
    allProfs.add(P1);
    allProfs.add(P2);

    auto C1 = new Course(111, "C1", "LVL", P1, "Mon 12:00", 6);
    allCourses.add(C1);

    auto S1 = new Student(33, "Stud", "studId template");
    allStuds.add(S1);

    auto A1 = new Admin(101, "Adm", "Admissions");
    allAdmins.add(A1);
}
int main() {
    collection<Professor*> allProfs;
    collection<Student*> allStuds;
    collection<Course*> allCourses;
    collection<Admin*> allAdmins;

    initCollectionData(allProfs, allStuds, allCourses, allAdmins);
    
    templatesMenu(allCourses, allStuds, allProfs, allAdmins);

    for (int i = 0; i < allCourses.getSize(); ++i) delete allCourses.get(i);
    for (int i = 0; i < allProfs.getSize(); ++i) delete allProfs.get(i);
    for (int i = 0; i < allStuds.getSize(); ++i) delete allStuds.get(i);
    for (int i = 0; i < allAdmins.getSize(); ++i) delete allAdmins.get(i);

    return 0;
}