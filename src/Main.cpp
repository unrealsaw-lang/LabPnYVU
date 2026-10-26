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
    auto P1_raw = P1.get();
    allProfs.add(P1.release());

    auto P2 = std::make_unique<Professor>(2, "Bob", "Native");
    auto P2_raw = P2.get();
    allProfs.add(P2.release());

    auto C1 = std::make_unique<Course>(1, "English", "A1", P1_raw, "Mon 12:00", 6);
    auto C1_raw = C1.get();
    allCourses.add(C1.release());

    auto C2 = std::make_unique<Course>(2, "Russian", "B2", P1_raw, "Mon 10:00", 12);
    auto C2_raw = C2.get();
    allCourses.add(C2.release());

    auto C3 = std::make_unique<Course>(3, "English", "A2", P1_raw, "Tue 10:00", 10);
    auto C3_raw = C3.get();
    allCourses.add(C3.release());

    auto S1 = std::make_unique<Student>(1, "Steve", "50128");
    auto S1_raw = S1.get();
    allStuds.add(S1.release());

    auto S2 = std::make_unique<Student>(2, "Bob", "44101");
    auto S2_raw = S2.get();
    allStuds.add(S2.release());

    auto S3 = std::make_unique<Student>(3, "Alex", "15223");
    auto S3_raw = S3.get();
    allStuds.add(S3.release());

    auto S4 = std::make_unique<Student>(4, "Andrew", "73077");
    auto S4_raw = S4.get();
    allStuds.add(S4.release());

    auto S5 = std::make_unique<Student>(5, "David", "22401");
    auto S5_raw = S5.get();
    allStuds.add(S5.release());

    auto S6 = std::make_unique<Student>(6, "George", "55940");
    auto S6_raw = S6.get();
    allStuds.add(S6.release());

    auto S7 = std::make_unique<Student>(7, "TEST", "TESTID");
    allStuds.add(S7.release());

    auto A1 = std::make_unique<Admin>(101, "Ann", "Admissions");
    allAdmins.add(A1.release());

    *C1_raw += S1_raw;
    *C1_raw += S2_raw;
    *C1_raw += S3_raw;
    *C1_raw += S4_raw;
    *C1_raw += S5_raw;
    *C1_raw += S6_raw;

    *C2_raw += S1_raw;
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
    catch (const std::exception& e) { std::cerr << "Error. Program will be closed safely\n"; }

    for (auto crs : allCourses) delete crs;
    for (auto prof : allProfs) delete prof;
    for (auto stud : allStuds) delete stud;
    for (auto adm : allAdmins) delete adm;

    return 0;
}