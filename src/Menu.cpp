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

void printResult(const std::string& a, const char* op, const std::string& b, bool r) {
    std::cout << a << " " << op << " " << b
        << " : " << (r ? "TRUE" : "FALSE") << "\n";
}

void compareCourses(const std::vector<Course*>& C) {
    int id1 = promptInt("A id: ");
    int id2 = promptInt("B id: ");
    const Course* A = findCourseById(C, id1);
    const Course* B = findCourseById(C, id2);
    if (!A || !B) { std::cout << "Not found\n"; return; }

    int op = promptInt("\n1.==  \n2.!=  \n3.<  \n4.>  \n5.<=  \n6.>= \nYour choice: ");
    static const char* sym[] = { "", "==", "!=", "<", ">", "<=", ">=" };
    bool r = false;
    if (op == 1) r = (*A == *B);
    else if (op == 2) r = (*A != *B);
    else if (op == 3) r = (*A < *B);
    else if (op == 4) r = (*A > *B);
    else if (op == 5) r = (*A <= *B);
    else if (op == 6) r = (*A >= *B);
    else { std::cout << "Invalid\n"; return; }

    std::string labelA = "Course(id=" + std::to_string(A->getId()) + ", "
        + A->getCourseLanguage() + " " + A->getCourseLevel() + ")";
    std::string labelB = "Course(id=" + std::to_string(B->getId()) + ", "
        + B->getCourseLanguage() + " " + B->getCourseLevel() + ")";

    printResult(labelA, sym[op], labelB, r);
}
void compareStudents(const std::vector<Student*>& S) {
    int id1 = promptInt("A id: ");
    int id2 = promptInt("B id: ");
    const Student* A = findStudentById(S, id1);
    const Student* B = findStudentById(S, id2);
    if (!A || !B) { std::cout << "Not found\n"; return; }

    int op = promptInt("\n1.==  \n2.!=  \n3.<  \n4.>  \n5.<=  \n6.>= \nYour choice: ");
    static const char* sym[] = { "", "==", "!=", "<", ">", "<=", ">=" };
    bool r = false;
    if (op == 1) r = (*A == *B);
    else if (op == 2) r = (*A != *B);
    else if (op == 3) r = (*A < *B);
    else if (op == 4) r = (*A > *B);
    else if (op == 5) r = (*A <= *B);
    else if (op == 6) r = (*A >= *B);
    else { std::cout << "Invalid\n"; return; }

    std::string labelA = "Student(id=" + std::to_string(A->getId())
        + ", " + A->getName() + ")";
    std::string labelB = "Student(id=" + std::to_string(B->getId())
        + ", " + B->getName() + ")";
    printResult(labelA, sym[op], labelB, r);
}
void compareProfessors(const std::vector<Professor*>& P) {
    int id1 = promptInt("A id: ");
    int id2 = promptInt("B id: ");
    const Professor* A = findProfessorById(P, id1);
    const Professor* B = findProfessorById(P, id2);
    if (!A || !B) { std::cout << "Not found\n"; return; }

    int op = promptInt("\n1.==  \n2.!=  \n3.<  \n4.>  \n5.<=  \n6.>= \nYour choice: ");
    static const char* sym[] = { "", "==", "!=", "<", ">", "<=", ">=" };
    bool r = false;
    if (op == 1) r = (*A == *B);
    else if (op == 2) r = (*A != *B);
    else if (op == 3) r = (*A < *B);
    else if (op == 4) r = (*A > *B);
    else if (op == 5) r = (*A <= *B);
    else if (op == 6) r = (*A >= *B);
    else { std::cout << "Invalid\n"; return; }

    std::string labelA = "Professor(id=" + std::to_string(A->getId())
        + ", " + A->getName() + ")";
    std::string labelB = "Professor(id=" + std::to_string(B->getId())
        + ", " + B->getName() + ")";
    printResult(labelA, sym[op], labelB, r);
}
void compareAdmins(const std::vector<Admin*>& A) {
    int id1 = promptInt("A id: ");
    int id2 = promptInt("B id: ");
    const Admin* a = findAdminById(A, id1);
    const Admin* b = findAdminById(A, id2);
    if (!a || !b) { std::cout << "Not found\n"; return; }

    int op = promptInt("\n1.==  \n2.!=  \n3.<  \n4.>  \n5.<=  \n6.>= \nYour choice: ");
    static const char* sym[] = { "", "==", "!=", "<", ">", "<=", ">=" };
    bool r = false;
    if (op == 1) r = (*a == *b);
    else if (op == 2) r = (*a != *b);
    else if (op == 3) r = (*a < *b);
    else if (op == 4) r = (*a > *b);
    else if (op == 5) r = (*a <= *b);
    else if (op == 6) r = (*a >= *b);
    else { std::cout << "Invalid\n"; return; }

    std::string labelA = "Admin(id=" + std::to_string(a->getId())
        + ", " + a->getName() + ", " + a->getResponsibility() + ")";
    std::string labelB = "Admin(id=" + std::to_string(b->getId())
        + ", " + b->getName() + ", " + b->getResponsibility() + ")";
    printResult(labelA, sym[op], labelB, r);
}

void outputById(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    int t = promptInt("\n1.Course \n2.Student \n3.Professor \n4.Admin \nYour choice ");
    int id = promptInt("Enter id: ");
    if (t == 1) { Course* x = findCourseById(allCourses, id);       if (x) std::cout << *x << "\n"; else std::cout << "Not found...\n"; }
    else if (t == 2) { Student* x = findStudentById(allStudents, id);     if (x) x->printInfo(); else std::cout << "Not found...\n"; }
    else if (t == 3) { Professor* x = findProfessorById(allProfs, id);      if (x) x->printInfo(); else std::cout << "Not found...\n"; }
    else if (t == 4) { Admin* x = findAdminById(allAdmins, id);         if (x) x->printInfo(); else std::cout << "Not found...\n"; }
}
void inputById(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    int t = promptInt("\n1.Course \n2.Student \n3.Professor \n4.Admin \nYour choice ");
    int id = promptInt("Enter id: ");

    if (t == 1) {
        Course* C = findCourseById(allCourses, id);
        if (!C) { std::cout << "Not found...\n"; return; }
        std::cin >> *C;
    }
    else if (t == 2) {
        Student* S = findStudentById(allStudents, id);
        if (!S) { std::cout << "Not found...\n"; return; }
        std::cin >> *S;
    }
    else if (t == 3) {
        Professor* P = findProfessorById(allProfs, id);
        if (!P) { std::cout << "Not found...\n"; return; }
        std::cin >> *P;
    }
    else if (t == 4) {
        Admin* A = findAdminById(allAdmins, id);
        if (!A) { std::cout << "Not found...\n"; return; }
        std::cin >> *A;
    }
    else std::cout << "Invalid\n";
}

void operatorsMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Compare two courses\n";
        std::cout << "2. Compare two students\n";
        std::cout << "3. Compare two professors\n";
        std::cout << "4. Compare two admins\n";
        std::cout << "5. Output <<\n";
        std::cout << "6. Input >>\n";
        std::cout << "7. Add student to course +=\n";
        std::cout << "8. Remove student from course -=\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) compareCourses(allCourses);
        else if (c == 2) compareStudents(allStudents);
        else if (c == 3) compareProfessors(allProfs);
        else if (c == 4) compareAdmins(allAdmins);
        else if (c == 5) outputById(allCourses, allStudents, allProfs, allAdmins);
        else if (c == 5) inputById(allCourses, allStudents, allProfs, allAdmins);
        else if (c == 7) {
            int cid = promptInt("Course id: ");
            Course* C = findCourseById(allCourses, cid);
            if (!C) { std::cout << "Course not found...\n"; continue; }
            int sid = promptInt("Student id: ");
            Student* S = findStudentById(allStudents, sid);
            if (!S) {
                int ch = promptInt("Not found. Create? 1-yes 2-no: ");
                if (ch != 1) continue;
                std::string n = promptName("Name: ");
                S = new Student(sid, n);
                allStudents.push_back(S);
            }
            *C += S;
            std::cout << "Students on course: " << C->getCourseCurrCount() << "\n";
        }
        else if (c == 8) {
            int cid = promptInt("Course id: ");
            Course* C = findCourseById(allCourses, cid);
            if (!C) { std::cout << "Course not found...\n"; continue; }
            int sid = promptInt("Student id: ");
            Student* S = findStudentById(allStudents, sid);
            if (!S) { std::cout << "Student not found...\n"; continue; }
            *C -= S;
            std::cout << "Students on course: " << C->getCourseCurrCount() << "\n";
        }
        else std::cout << "Invalid\n";
    }
}

void adminLogicMenu(std::vector<Admin*>& allAdmins, std::vector<Course*>& allCourses)
{
    if (allAdmins.empty()) { std::cout << "\nNo admins\n"; return; }

    int id = promptInt("Admin id: ");
    Admin* A = findAdminById(allAdmins, id);
    if (!A) { std::cout << "Not found\n"; return; }

    std::cout << "\n1. Add course to admin (+=)\n";
    std::cout << "2. Remove course from admin (-=)\n";
    std::cout << "3. Show admin info\n";
    int c = promptInt("Choice: ");

    if (c == 1) {
        int cid = promptInt("Course id: ");
        Course* C = findCourseById(allCourses, cid);
        if (!C) { std::cout << "Course not found\n"; return; }
        *A += C;
    }
    else if (c == 2) {
        int cid = promptInt("Course id: ");
        Course* C = findCourseById(allCourses, cid);
        if (!C) { std::cout << "Course not found\n"; return; }
        *A -= C;
    }
    else if (c == 3) {
        A->printInfo();
    }
}
void showAllAsPerson(const std::vector<Student*>& allStudents, const std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    std::vector<Person*> everyone;
    for (Student* s : allStudents) everyone.push_back(s);
    for (Professor* p : allProfs)  everyone.push_back(p);
    for (Admin* a : allAdmins)     everyone.push_back(a);

    std::cout << "Collection size: " << everyone.size() << " people\n";

    for (Person* p : everyone) {
        std::cout << "\n" << p->getType() << "\n";
        std::cout << "id=" << p->getId() << ", name=" << p->getName() << "\n";
        p->printInfo();
    }
}
void showInheritedMethods(const std::vector<Student*>& allStudents, const std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    std::cout << "\ngetId(), getName(), operator== are defined ONCE in Person\n\n";

    if (!allStudents.empty()) std::cout << "Student   : id=" << allStudents[0]->getId() << ", name=" << allStudents[0]->getName() << "\n";
    if (!allProfs.empty()) std::cout << "Professor : id=" << allProfs[0]->getId() << ", name=" << allProfs[0]->getName() << "\n";
    if (!allAdmins.empty()) std::cout << "Admin     : id=" << allAdmins[0]->getId() << ", name=" << allAdmins[0]->getName() << "\n";

    if (allStudents.size() >= 2) {
        std::cout << "\noperator==  inherited from Person\n";
        std::cout << "  Student(" << allStudents[0]->getId() << ")" << " == Student(" << allStudents[1]->getId() << ") : " << (*allStudents[0] == *allStudents[1] ? "TRUE" : "FALSE") << "\n";
    }
}
void showVirtualMethods(const std::vector<Student*>& allStudents,const std::vector<Professor*>& allProfs, const std::vector<Admin*>& allAdmins) {
    std::vector<Person*> everyone;
    for (Student* s : allStudents) everyone.push_back(s);
    for (Professor* p : allProfs)  everyone.push_back(p);
    for (Admin* a : allAdmins)     everyone.push_back(a);

    int totalWorkload = 0;
    int i = 1;
    for (Person* p : everyone) {
        std::string type = p->getType();
        int workload = p->getWorkload();
        totalWorkload += workload;

        std::cout << i++ << ") getType()     - " << type << "\n";
        std::cout << "   getWorkload() - " << workload << " h/week\n";
    }

    std::cout << "--------------------------------------------\n";
    std::cout << "Total weekly workload: " << totalWorkload << " hours\n";
    std::cout << "This number was computed polymorphically:\n";
    std::cout << "each getWorkload() returned a DIFFERENT value\n";
}
void inheritanceMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Show polymorphism (Person*)\n";
        std::cout << "2. Show inherited methods\n";
        std::cout << "3. Show virtual methods (getType/getWorkload)\n";
        std::cout << "4. Admin logic\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) showAllAsPerson(allStudents, allProfs, allAdmins);
        else if (c == 2) showInheritedMethods(allStudents, allProfs, allAdmins);
        else if (c == 3) showVirtualMethods(allStudents, allProfs, allAdmins);
        else if (c == 4) adminLogicMenu(allAdmins, allCourses);
        else std::cout << "Invalid\n";
    }
}


void printMenu(std::vector<Course*>& allCourses,std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
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
        else if (c == 2) { for (Student* x : allStudents) x->printInfo(); }
        else if (c == 3) { for (Professor* x : allProfs) x->printInfo(); }
        else if (c == 4) { for (Admin* x : allAdmins) x->printInfo(); }
        else if (c == 5) { int id = promptInt("id: "); Course* x = findCourseById(allCourses, id); if (x) x->printCourse(); else std::cout << "Not found\n"; }
        else if (c == 6) { int id = promptInt("id: "); Student* x = findStudentById(allStudents, id); if (x) x->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 7) { int id = promptInt("id: "); Professor* x = findProfessorById(allProfs, id); if (x) x->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 8) { int id = promptInt("id: "); Admin* x = findAdminById(allAdmins, id); if (x) x->printInfo(); else std::cout << "Not found\n"; }
        else std::cout << "Invalid\n";
    }
}

void createMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
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
            int max = promptInt("Max capacity: ");

            Professor* P = findProfessorByName(allProfs, pname);
            if (!P) {
                int pid = promptInt("Professor not found. New id: ");
                P = new Professor(pid, pname);
                allProfs.push_back(P);
            }
            allCourses.push_back(new Course(id, lang, lvl, P, sched, max));
            std::cout << "Course created\n";
        }
        else if (c == 2) {
            int id = promptInt("Student id: ");
            std::string name = promptName("Name: ");
            allStudents.push_back(new Student(id, name));
            std::cout << "Student created\n";
        }
        else if (c == 3) {
            int id = promptInt("Professor id: ");
            std::string name = promptName("Name: ");
            allProfs.push_back(new Professor(id, name));
            std::cout << "Professor created\n";
        }
        else if (c == 4) {
            int id = promptInt("Admin id: ");
            std::string name = promptName("Name: ");
            std::string dept = promptName("Department: ");
            allAdmins.push_back(new Admin(id, name, dept));
            std::cout << "Admin created\n";
        }
        else std::cout << "Invalid\n";
    }
}

void deleteMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins) {
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
            for (Student* s : allStudents) *s -= C;
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
            Student* S = findStudentById(allStudents, sid);
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
            for (size_t i = 0; i < allStudents.size(); ++i) {
                if (allStudents[i]->getId() == id) {
                    Student* S = allStudents[i];
                    for (Course* C : allCourses) *C -= S;
                    delete S;
                    allStudents.erase(allStudents.begin() + i);
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