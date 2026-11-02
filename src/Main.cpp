#include <iostream>
#include <string>
#include <memory>
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include "Collection.h"
#include "Menu.h"

void initData(collection<Professor*>& allProfs, collection<Student*>& allStuds, collection<Course*>& allCourses, collection<Admin*>& allAdmins) {
    auto P1 = std::make_unique<Professor>(1, "Andrew", "Foreign");
    auto rawP1 = P1.get();
    allProfs.add(P1.release());

    auto P2 = std::make_unique<Professor>(2, "Bob", "Native");
    auto rawP2 = P2.get();
    allProfs.add(P2.release());

    auto C1 = std::make_unique<Course>(1, "English", "A1", rawP1, "Mon 12:00", 6);
    auto rawC1 = C1.get();
    allCourses.add(C1.release());

    auto C2 = std::make_unique<Course>(2, "Russian", "B2", rawP1, "Mon 10:00", 12);
    auto rawC2 = C2.get();
    allCourses.add(C2.release());

    auto C3 = std::make_unique<Course>(3, "English", "A2", rawP1, "Tue 10:00", 10);
    auto rawC3 = C3.get();
    allCourses.add(C3.release());

    auto S1 = std::make_unique<Student>(1, "Steve", "50128");
    auto rawS1 = S1.get();
    allStuds.add(S1.release());

    auto S2 = std::make_unique<Student>(2, "Bob", "44101");
    auto rawS2 = S2.get();
    allStuds.add(S2.release());

    auto S3 = std::make_unique<Student>(3, "Alex", "15223");
    auto rawS3 = S3.get();
    allStuds.add(S3.release());

    auto S4 = std::make_unique<Student>(4, "Andrew", "73077");
    auto rawS4 = S4.get();
    allStuds.add(S4.release());

    auto S5 = std::make_unique<Student>(5, "David", "22401");
    auto rawS5 = S5.get();
    allStuds.add(S5.release());

    auto S6 = std::make_unique<Student>(6, "George", "55940");
    auto rawS6 = S6.get();
    allStuds.add(S6.release());

    auto S7 = std::make_unique<Student>(7, "TEST", "TESTID");
    allStuds.add(S7.release());

    auto A1 = std::make_unique<Admin>(101, "Ann", "Admissions");
    allAdmins.add(A1.release());

    *rawC1 += rawS1;
    *rawC1 += rawS2;
    *rawC1 += rawS3;
    *rawC1 += rawS4;
    *rawC1 += rawS5;
    *rawC1 += rawS6;

    *rawC2 += rawS1;
}

int main() {
    collection<Professor*> allProfs;
    collection<Student*> allStuds;
    collection<Course*> allCourses;
    collection<Admin*> allAdmins;
    
    try {
        initData(allProfs, allStuds, allCourses, allAdmins);
        mainMenu(allCourses, allStuds, allProfs, allAdmins);
    }
    catch (const myException& e) { std::cerr << "Error. Program will be closed safely\n"; }

    for (auto crs : allCourses) delete crs;
    for (auto prof : allProfs) delete prof;
    for (auto stud : allStuds) delete stud;
    for (auto adm : allAdmins) delete adm;

    return 0;
}