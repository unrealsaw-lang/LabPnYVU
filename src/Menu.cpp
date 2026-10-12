#include "Menu.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include <iostream>

std::string promptName(const std::string& prompt) {
    std::cout << prompt;
    std::string n;
    std::getline(std::cin, n);
    return n;
}
int promptInt(const std::string& prompt) {
    std::cout << prompt;
    int v;
    std::cin >> v;
    std::cin.ignore();
    return v;
}

Course* findCourseById(const std::vector<Course*>& v, int id) {
    for (Course* C : v) if (C->getId() == id) return C;
    return nullptr;
}
Student* findStudentById(const std::vector<Student*>& v, int id) {
    for (Student* S : v) if (S->getId() == id) return S;
    return nullptr;
}
Professor* findProfessorById(const std::vector<Professor*>& v, int id) {
    for (Professor* P : v) if (P->getId() == id) return P;
    return nullptr;
}
Admin* findAdminById(const std::vector<Admin*>& v, int id) {
    for (Admin* A : v) if (A->getId() == id) return A;
    return nullptr;
}
Student* findStudentByName(const std::vector<Student*>& v, const std::string& name) {
    for (Student* S : v) if (S->getName() == name) return S;
    return nullptr;
}
Professor* findProfessorByName(const std::vector<Professor*>& v, const std::string& name) {
    for (Professor* P : v) if (P->getName() == name) return P;
    return nullptr;
}
Course* findCourseByTitle(const std::vector<Course*>& v) {
    std::string t, l;
    std::cout << "Course language: "; std::cin >> t;
    std::cout << "Course level: ";    std::cin >> l;
    std::cin.ignore();
    for (Course* C : v)
        if (C->getCourseLanguage() == t && C->getCourseLevel() == l) return C;
    return nullptr;
}

static void showPolymorphism(const std::vector<Student*>& allStuds, const std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    std::vector<Person*> everyone;
    for (Student* s : allStuds) everyone.push_back(s);
    for (Professor* p : allProfs)  everyone.push_back(p);
    for (Admin* a : allAdmins)     everyone.push_back(a);

    std::cout << "\nCollection size: " << everyone.size() << " people\n";

    int i = 1;
    for (Person* p : everyone) {
        std::cout << "\n" << i++ << ") " << p->getType()
            << " (id = " << p->getId()
            << ", name: " << p->getName()
            << ", courses = " << p->getCount() << ")\n";
        p->printInfo();
    }
}
static void showInheritedMethods(const std::vector<Student*>& allStuds, const std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    if (!allStuds.empty()) {
        const Student* s = allStuds[0];
        std::cout << "\nclass Student:\n";
        std::cout << "[inherited] id            = " << s->getId() << "\n";
        std::cout << "[inherited] name          = " << s->getName() << "\n";
        std::cout << "[inherited] courses count = " << s->getCount() << "\n";
        std::cout << "[special] studentId       = " << s->getStudentId() << "\n";
        std::cout << "[override] getType()      = " << s->getType() << "\n";
        std::cout << "[override] calculateWorkload()  = " << s->calculateWorkload() << " h/week\n";
    }

    if (!allProfs.empty()) {
        const Professor* p = allProfs[0];
        std::cout << "\nclass Professor:\n";
        std::cout << "[inherited] id            = " << p->getId() << "\n";
        std::cout << "[inherited] name          = " << p->getName() << "\n";
        std::cout << "[inherited] courses count = " << p->getCount() << "\n";
        std::cout << "[special] department      = " << p->getDepartment() << "\n";
        std::cout << "[override] getType()      = " << p->getType() << "\n";
        std::cout << "[override] calculateWorkload()  = " << p->calculateWorkload() << " h/week\n";
    }

    if (!allAdmins.empty()) {
        const Admin* a = allAdmins[0];
        std::cout << "\nclass Admin:\n";
        std::cout << "[inherited] id             = " << a->getId() << "\n";
        std::cout << "[inherited] name           = " << a->getName() << "\n";
        std::cout << "[inherited] courses count  = " << a->getCount() << "\n";
        std::cout << "[special] responsibility   = " << a->getResponsibility() << "\n";
        std::cout << "[override] getType()       = " << a->getType() << "\n";
        std::cout << "[override] calculateWorkload()   = " << a->calculateWorkload() << " h/week\n";
    }
}
static void showVirtualMethods(const std::vector<Student*>& allStuds, const std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    std::vector<Person*> everyone;
    for (Student* s : allStuds) everyone.push_back(s);
    for (Professor* p : allProfs)  everyone.push_back(p);
    for (Admin* a : allAdmins)     everyone.push_back(a);

    int totalWorkload = 0;
    int i = 1;
    for (Person* p : everyone) {
        int w = p->calculateWorkload();
        totalWorkload += w;
        std::cout << p->getName() << "(" << i++ << ") getType()     - " << p->getType() << "\n";
        std::cout << "   calculateWorkload() - " << w << " h/week\n";
    }

    std::cout << "--------------------------------------------\n";
    std::cout << "Total weekly workload: " << totalWorkload << " hours\n";
}
static void showAdminLogic(std::vector<Admin*>& allAdmins, std::vector<Course*>& allCourses) {
    if (allAdmins.empty()) { std::cout << "\nNo admins\n"; return; }

    int id = promptInt("Admin id: ");
    Admin* A = findAdminById(allAdmins, id);
    if (!A) { std::cout << "Not found\n"; return; }

    std::cout << "\n1. Add course to admin (+=)\n";
    std::cout << "2. Remove course from admin (-=)\n";
    std::cout << "3. Show admin info\n";
    std::cout << "4. Calculate dominant language (special method)\n";
    int c = promptInt("Choice: ");

    if (c == 1) {
        int cid = promptInt("Course id: ");
        Course* C = findCourseById(allCourses, cid);
        if (!C) { std::cout << "Course not found\n"; return; }
        std::cout << "Success!\n";
        *A += C;
    }
    else if (c == 2) {
        int cid = promptInt("Course id: ");
        Course* C = findCourseById(allCourses, cid);
        if (!C) { std::cout << "Course not found\n"; return; }
        std::cout << "Success!\n";
        *A -= C;
    }
    else if (c == 3) A->printInfo();
    else if (c == 4)A->calculateDominantLanguage();
}
static void markStudentMenu(std::vector<Student*>& allStuds) {
    int id; std::cout << "Enter student id: ";
    std::cin >> id;
    Student* S = findStudentById(allStuds, id);
    S->studentMarkInfo(S);
}
static void rateProfessorMenu(std::vector<Professor*>& allProfs) {
    int id; std::cout << "Enter professor id: ";
    std::cin >> id;
    Professor* P = findProfessorById(allProfs, id);
    P->professorRateMenu(P);
}
static void showVirtualDestructor() {
    std::cout << "\nVirtual ~Person() show: \n";

    Person* P1 = new Student(001, "TempStudent", "testStudentId");
    Person* P2 = new Professor(002, "TempProfessor", "testDepartment");
    Person* P3 = new Admin(003, "TempAdmin", "testResponsibility"); 
    Student* S = static_cast<Student*>(P1);
    S->addMark(5);
    S->addMark(4);
    Professor* P = static_cast<Professor*>(P2);
    P->rate(2);

    P1->printInfo();
    P2->printInfo();
    P3->printInfo();

    std::cout << '\n';

    delete P1;
    delete P2;
    delete P3;
}
void inheritanceMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStuds, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Show polymorphism\n";
        std::cout << "2. Show inherited methods\n";
        std::cout << "3. Show virtual methods\n";
        std::cout << "4. Admin logic\n";
        std::cout << "5. Add mark to student (special method)\n";
        std::cout << "6. Rate professor (special method)\n";
        std::cout << "7. Show virtual destructor\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) showPolymorphism(allStuds, allProfs, allAdmins);
        else if (c == 2) showInheritedMethods(allStuds, allProfs, allAdmins);
        else if (c == 3) showVirtualMethods(allStuds, allProfs, allAdmins);
        else if (c == 4) showAdminLogic(allAdmins, allCourses);
        else if (c == 5) markStudentMenu(allStuds);
        else if (c == 6) rateProfessorMenu(allProfs);
        else if (c == 7)showVirtualDestructor();
        else std::cout << "Invalid\n";
    }
}

void printMenu(std::vector<Course*>& allCourses,std::vector<Student*>& allStuds,std::vector<Professor*>& allProfs,std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. All courses\n";
        std::cout << "2. All students\n";
        std::cout << "3. All professors\n";
        std::cout << "4. All admins\n";
        std::cout << "5. Course by id\n";
        std::cout << "6. Student by id\n";
        std::cout << "7. Professor by id\n";
        std::cout << "8. Admin by id\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) { for (Course* x : allCourses) x->printCourse(); }
        else if (c == 2) { for (Student* x : allStuds) x->printInfo(); }
        else if (c == 3) { for (Professor* x : allProfs) x->printInfo(); }
        else if (c == 4) { for (Admin* x : allAdmins) x->printInfo(); }
        else if (c == 5) { int id = promptInt("id: "); Course* x = findCourseById(allCourses, id); if (x) x->printCourse(); else std::cout << "Not found\n"; }
        else if (c == 6) { int id = promptInt("id: "); Student* x = findStudentById(allStuds, id); if (x) x->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 7) { int id = promptInt("id: "); Professor* x = findProfessorById(allProfs, id); if (x) x->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 8) { int id = promptInt("id: "); Admin* x = findAdminById(allAdmins, id); if (x) x->printInfo(); else std::cout << "Not found\n"; }
        else std::cout << "Invalid\n";
    }
}
void createMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStuds, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Course\n2. Student\n3. Professor\n4. Admin\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) {
            int id = promptInt("Course id: ");
            std::string lang = promptName("Language: ");
            std::string lvl = promptName("Level: ");
            std::string pname = promptName("Professor name: ");
            std::string sched = promptName("Schedule: ");
            std::string dep = promptName("Department: ");
            int max = promptInt("Max capacity: ");

            Professor* P = findProfessorByName(allProfs, pname);
            if (!P) {
                int pid = promptInt("Professor not found. New id: ");
                P = new Professor(pid, pname, dep);
                allProfs.push_back(P);
            }
            allCourses.push_back(new Course(id, lang, lvl, P, sched, max));
            std::cout << "Course created!\n";
        }
        else if (c == 2) {
            int id = promptInt("Student id: ");
            std::string name = promptName("Name: "); 
            std::string sId = promptName("Student ID: ");
            allStuds.push_back(new Student(id, name, sId));
            std::cout << "Student created!\n";
        }
        else if (c == 3) {
            int id = promptInt("Professor id: ");
            std::string name = promptName("Name: ");
            std::string dep = promptName("Department: ");
            allProfs.push_back(new Professor(id, name, dep));
            std::cout << "Professor created!\n";
        }
        else if (c == 4) {
            int id = promptInt("Admin id: ");
            std::string name = promptName("Name: ");
            std::string resp = promptName("Responsibility: ");
            allAdmins.push_back(new Admin(id, name, resp));
            std::cout << "Admin created!\n";
        }
        else std::cout << "Invalid\n";
    }
}
void deleteMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStuds, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Delete course\n";
        std::cout << "2. Delete student from course\n";
        std::cout << "3. Remove professor from course\n";
        std::cout << "4. Delete student\n";
        std::cout << "5. Delete professor\n";
        std::cout << "6. Delete admin\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) {
            Course* C = findCourseByTitle(allCourses);
            if (!C) { std::cout << "Course not found...\n"; continue; }
            for (Student* s : allStuds) *s -= C;
            for (Professor* p : allProfs) *p -= C;
            for (Admin* a : allAdmins) *a -= C;
            for (size_t i = 0; i < allCourses.size(); ++i) {
                if (allCourses[i] == C) {
                    delete C;
                    allCourses.erase(allCourses.begin() + i);
                    break;
                }
            }
            std::cout << "Course deleted!\n";
        }
        else if (c == 2) {
            int cid = promptInt("Course id: ");
            Course* C = findCourseById(allCourses, cid);
            if (!C) { std::cout << "Course not found...\n"; continue; }
            int sid = promptInt("Student id: ");
            Student* S = findStudentById(allStuds, sid);
            if (!S) { std::cout << "Student not found...\n"; continue; }
            *C -= S;
        }
        else if (c == 3) {
            int cid = promptInt("Course id: ");
            Course* C = findCourseById(allCourses, cid);
            if (!C) { std::cout << "Course not found...\n"; continue; }
            int pid = promptInt("Professor id: ");
            Professor* P = findProfessorById(allProfs, pid);
            if (!P) { std::cout << "Professor not found...\n"; continue; }
            *C -= P;
        }
        else if (c == 4) {
            int id = promptInt("Student id: ");
            for (size_t i = 0; i < allStuds.size(); ++i) {
                if (allStuds[i]->getId() == id) {
                    Student* S = allStuds[i];
                    for (Course* C : allCourses) *C -= S;
                    delete S;
                    allStuds.erase(allStuds.begin() + i);
                    std::cout << "Deleted!\n";
                    break;
                }
            }
        }
        else if (c == 5) {
            int id = promptInt("Professor id: ");
            for (size_t i = 0; i < allProfs.size(); ++i) {
                if (allProfs[i]->getId() == id) {
                    Professor* P = allProfs[i];
                    for (Course* C : allCourses) *C -= P;
                    delete P;
                    allProfs.erase(allProfs.begin() + i);
                    std::cout << "Deleted!\n";
                    break;
                }
            }
        }
        else if (c == 6) {
            int id = promptInt("Admin id: ");
            for (size_t i = 0; i < allAdmins.size(); ++i) {
                if (allAdmins[i]->getId() == id) {
                    delete allAdmins[i];
                    allAdmins.erase(allAdmins.begin() + i);
                    std::cout << "Deleted!\n";
                    break;
                }
            }
        }
    }
}
void enrollMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStuds, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Add student to course\n";
        std::cout << "2. Add professor to course\n";
        std::cout << "3. Add admin to course\n";
        std::cout << "4. Remove student from course\n";
        std::cout << "5. Remove professor from course\n";
        std::cout << "6. Remove admin from course\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;
        if (c < 1 || c > 6) { std::cout << "Invalid\n"; continue; }

        int cid = promptInt("Course id: ");
        Course* C = findCourseById(allCourses, cid);
        if (!C) { std::cout << "Course not found...\n"; continue; }

        if (c == 1 || c == 4) {
            int sid = promptInt("Student id: ");
            Student* S = findStudentById(allStuds, sid);
            if (!S) { std::cout << "Student not found...\n"; continue; }

            if (c == 1) {
                int before = S->getCount();
                *S += C;
                if (S->getCount() > before) std::cout << "Student added!\n";
            }
            else {
                *C -= S;
            }
        }
        else if (c == 2 || c == 5) {
            int pid = promptInt("Professor id: ");
            Professor* P = findProfessorById(allProfs, pid);
            if (!P) { std::cout << "Professor not found...\n"; continue; }

            if (c == 2) {
                int before = P->getCount();
                *P += C;
                if (P->getCount() > before) std::cout << "Professor added!\n";
            }
            else {
                *C -= P;
            }
        }
        else {
            int aid = promptInt("Admin id: ");
            Admin* A = findAdminById(allAdmins, aid);
            if (!A) { std::cout << "Admin not found...\n"; continue; }

            if (c == 3) {
                int before = A->getCount();
                *A += C;
                if (A->getCount() > before) std::cout << "Admin added!\n";
            }
            else {
                int before = A->getCount();
                *A -= C;
                if (A->getCount() < before) std::cout << "Admin removed!\n";
            }
        }
    }
}