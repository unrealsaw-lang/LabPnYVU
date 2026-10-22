#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include "Collection.h"
#include "Menu.h"

void initData(collection<Professor*>& allProfs, collection<Student*>& allStuds, collection<Course*>& allCourses, collection<Admin*>& allAdmins) {
    auto P1 = new Professor(1, "Andrew", "Foreign");
    auto P2 = new Professor(2, "Bob", "Native");
    allProfs.add(P1);
    allProfs.add(P2);

    auto C1 = new Course(1, "English", "A1", P1, "Mon 12:00", 6);
    auto C2 = new Course(2, "Russian", "B2", P1, "Mon 10:00", 12);
    auto C3 = new Course(3, "English", "A2", P1, "Tue 10:00", 10);
    allCourses.add(C1);
    allCourses.add(C2);
    allCourses.add(C3);

    auto S1 = new Student(1, "Steve", "50128");
    auto S2 = new Student(2, "Bob", "44101");
    auto S3 = new Student(3, "Alex", "15223");
    auto S4 = new Student(4, "Andrew", "73077");
    auto S5 = new Student(5, "David", "22401");
    auto S6 = new Student(6, "George", "55940");
    auto S7 = new Student(7, "TEST", "TESTID");
    allStuds.add(S1);
    allStuds.add(S2);
    allStuds.add(S3); 
    allStuds.add(S4);
    allStuds.add(S5);
    allStuds.add(S6);
    allStuds.add(S7);

    auto A1 = new Admin(101, "Ann", "Admissions");
    allAdmins.add(A1);

    *C1 += S1;
    *C1 += S2;
    *C1 += S3;
    *C1 += S4;
    *C1 += S5;
    *C1 += S6;

    *C2 += S1;
}
int main() {
    collection<Professor*> allProfs;
    collection<Student*> allStuds;
    collection<Course*> allCourses;
    collection<Admin*> allAdmins;

    initData(allProfs, allStuds, allCourses, allAdmins);
    
    templatesMenu(allCourses, allStuds, allProfs, allAdmins);

    for (int i = 0; i < allCourses.getSize(); ++i) delete allCourses.get(i);
    for (int i = 0; i < allProfs.getSize(); ++i) delete allProfs.get(i);
    for (int i = 0; i < allStuds.getSize(); ++i) delete allStuds.get(i);
    for (int i = 0; i < allAdmins.getSize(); ++i) delete allAdmins.get(i);

    return 0;
}