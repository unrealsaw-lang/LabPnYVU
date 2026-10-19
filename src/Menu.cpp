#include "Menu.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include <iostream>

template <typename T> static void addToCollection(T* obj, collection<T*>& col) {
    if (obj) { col.add(obj); std::cout << "\nSuccess!"; }
    else     std::cout << "\nNull!";
}

template <typename T> static void removeFromCollection(T* obj, collection<T*>& col) {
    if (obj) { col.remove(obj); std::cout << "\nSuccess!"; }
    else     std::cout << "\nNull!";
}

template <typename T> static void getCollectionSize(collection<T*>& col) {
    if (col.getSize() != 0) std::cout << "\nSize of the collection: " << col.getSize();
    else                    std::cout << "\nCollection is empty...";
}

std::string promptName(const std::string& prompt) {
    std::cout << prompt;
    std::string n;
    std::getline(std::cin, n);
    return n;
}

int promptInt(const std::string& prompt) {
    std::cout << prompt;
    int v; std::cin >> v; std::cin.ignore();
    return v;
}

static Course* findCourse(const collection<Course*>& allCourses) {
    while (true) {
        std::cout << "\n1. By id\n2. By language\n3. By level\n"
            "4. By schedule\n5. By student count\n"
            "6. By professor count\n7. By max count\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Course* found = nullptr;
        if (c == 1) { int id = promptInt("Enter id: "); found = allCourses.findBy([&](Course* C) { return C->getId() == id; }); }
        else if (c == 2) { std::string s = promptName("Enter language: "); found = allCourses.findBy([&](Course* C) { return C->getLanguage() == s; }); }
        else if (c == 3) { std::string s = promptName("Enter level: "); found = allCourses.findBy([&](Course* C) { return C->getLevel() == s; }); }
        else if (c == 4) { std::string s = promptName("Enter schedule: "); found = allCourses.findBy([&](Course* C) { return C->getSchedule() == s; }); }
        else if (c == 5) { int n = promptInt("Enter student count: "); found = allCourses.findBy([&](Course* C) { return C->getStudentCount() == n; }); }
        else if (c == 6) { int n = promptInt("Enter professor count: "); found = allCourses.findBy([&](Course* C) { return C->getProfessorCount() == n; }); }
        else if (c == 7) { int n = promptInt("Enter max count: "); found = allCourses.findBy([&](Course* C) { return C->getMaxCount() == n; }); }

        if (found) return found;
        std::cout << "\nNot found\n";
    }
}

static Student* findStudent(const collection<Student*>& allStuds) {
    while (true) {
        std::cout << "\n1. By id\n2. By student id\n3. By name\n"
            "4. By course count\n5. By average grade\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Student* found = nullptr;
        if (c == 1) { int id = promptInt("Enter id: "); found = allStuds.findBy([&](Student* S) { return S->getId() == id; }); }
        else if (c == 2) { std::string s = promptName("Enter student id: "); found = allStuds.findBy([&](Student* S) { return S->getStudentId() == s; }); }
        else if (c == 3) { std::string s = promptName("Enter name: "); found = allStuds.findBy([&](Student* S) { return S->getName() == s; }); }
        else if (c == 4) { int n = promptInt("Enter course count: "); found = allStuds.findBy([&](Student* S) { return S->getCount() == n; }); }
        else if (c == 5) { double a = promptInt("Enter min average: "); found = allStuds.findBy([&](Student* S) { return S->calculateAverageMark() > a; }); }

        if (found) return found;
        std::cout << "\nNot found\n";
    }
}

static Professor* findProfessor(const collection<Professor*>& allProfs) {
    while (true) {
        std::cout << "\n1. By id\n2. By department\n3. By name\n"
            "4. By course count\n5. By average rating\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Professor* found = nullptr;
        if (c == 1) { int id = promptInt("Enter id: "); found = allProfs.findBy([&](Professor* P) { return P->getId() == id; }); }
        else if (c == 2) { std::string s = promptName("Enter department: "); found = allProfs.findBy([&](Professor* P) { return P->getDepartment() == s; }); }
        else if (c == 3) { std::string s = promptName("Enter name: "); found = allProfs.findBy([&](Professor* P) { return P->getName() == s; }); }
        else if (c == 4) { int n = promptInt("Enter course count: "); found = allProfs.findBy([&](Professor* P) { return P->getCount() == n; }); }
        else if (c == 5) { double a = promptInt("Enter min average: "); found = allProfs.findBy([&](Professor* P) { return P->calculateAverageRating() > a; }); }

        if (found) return found;
        std::cout << "\nNot found...\n";
    }
}

static Admin* findAdmin(const collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. By id\n2. By responsibility\n3. By name\n4. By course count\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Admin* found = nullptr;
        if (c == 1) { int id = promptInt("Enter id: "); found = allAdmins.findBy([&](Admin* A) { return A->getId() == id; }); }
        else if (c == 2) { std::string s = promptName("Enter responsibility: "); found = allAdmins.findBy([&](Admin* A) { return A->getResponsibility() == s; }); }
        else if (c == 3) { std::string s = promptName("Enter name: "); found = allAdmins.findBy([&](Admin* A) { return A->getName() == s; }); }
        else if (c == 4) { int n = promptInt("Enter course count: "); found = allAdmins.findBy([&](Admin* A) { return A->getCount() == n; }); }

        if (found) return found;
        std::cout << "\nNot found\n";
    }
}

void templatesMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Find object in collection\n2. Get object from collection\n"
            "3. Add object to collection\n4. Remove object from collection\n"
            "5. Get collection size\n6. Clear collection\n"
            "7. Demo with different data types\n8. Print\n9. Print courses by language and level\n0. Back";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        int subC;
        if (c == 1) {
            while (true) {
                std::cout << "\n1. Find student\n2. Find professor\n3. Find admin\n4. Find course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                if (subC == 1) { auto* f = findStudent(allStuds); if (f) f->printInfo(); }
                else if (subC == 2) { auto* f = findProfessor(allProfs); if (f) f->printInfo(); }
                else if (subC == 3) { auto* f = findAdmin(allAdmins); if (f) f->printInfo(); }
                else if (subC == 4) { auto* f = findCourse(allCourses); if (f) f->printInfo(); }
                else std::cout << "\nInvalid!";
            }
        }
        else if (c == 2) {
            while (true) {
                std::cout << "\n1. Get student\n2. Get professor\n3. Get admin\n4. Get course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                int idx = promptInt("Enter index: ");
                if (subC == 1) { auto* S = allStuds.get(idx); if (S) S->printInfo(); }
                else if (subC == 2) { auto* P = allProfs.get(idx); if (P) P->printInfo(); }
                else if (subC == 3) { auto* A = allAdmins.get(idx); if (A) A->printInfo(); }
                else if (subC == 4) { auto* C = allCourses.get(idx); if (C) C->printInfo(); }
                else std::cout << "\nInvalid!\n";
            }
        }
        else if (c == 3) {
            while (true) {
                std::cout << "\n1. Add student\n2. Add professor\n3. Add admin\n4. Add course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                if (subC == 1) {
                    int id = promptInt("Student id: ");
                    auto name = promptName("Name: ");
                    auto sid = promptName("Student ID: ");
                    addToCollection(new Student(id, name, sid), allStuds);
                }
                else if (subC == 2) {
                    int id = promptInt("Professor id: ");
                    auto name = promptName("Name: ");
                    auto dep = promptName("Department: ");
                    addToCollection(new Professor(id, name, dep), allProfs);
                }
                else if (subC == 3) {
                    int id = promptInt("Admin id: ");
                    auto name = promptName("Name: ");
                    auto resp = promptName("Responsibility: ");
                    addToCollection(new Admin(id, name, resp), allAdmins);
                }
                else if (subC == 4) {
                    int id = promptInt("Course id: ");
                    auto lang = promptName("Language: ");
                    auto lvl = promptName("Level: ");
                    auto pn = promptName("Professor name: ");
                    auto sch = promptName("Schedule: ");
                    int mx = promptInt("Max capacity: ");
                    Professor* P = allProfs.findBy([&](Professor* p) { return p->getName() == pn; });
                    if (!P) {
                        int pid = promptInt("Professor not found. New id: ");
                        auto dep = promptName("Department: ");
                        P = new Professor(pid, pn, dep);
                        allProfs.add(P);
                    }
                    addToCollection(new Course(id, lang, lvl, P, sch, mx), allCourses);
                }
                else std::cout << "\nInvalid!\n";
            }
        }
        else if (c == 4) {
            while (true) {
                std::cout << "\n1. Remove student\n2. Remove professor\n3. Remove admin\n4. Remove course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                if (subC == 1) removeFromCollection(findStudent(allStuds), allStuds);
                else if (subC == 2) removeFromCollection(findProfessor(allProfs), allProfs);
                else if (subC == 3) removeFromCollection(findAdmin(allAdmins), allAdmins);
                else if (subC == 4) removeFromCollection(findCourse(allCourses), allCourses);
                else std::cout << "\nInvalid!";
            }
        }
        else if (c == 5) {
            std::cout << "\n1. Students\n2. Professors\n3. Admins\n4. Courses\n0. Back\n";
            subC = promptInt("Your choice: ");
            if (subC == 1) getCollectionSize(allStuds);
            else if (subC == 2) getCollectionSize(allProfs);
            else if (subC == 3) getCollectionSize(allAdmins);
            else if (subC == 4) getCollectionSize(allCourses);
        }
        else if (c == 6) {
            std::cout << "\n1. Students\n2. Professors\n3. Admins\n4. Courses\n0. Back\n";
            subC = promptInt("Your choice: ");
            if (subC == 1) allStuds.clear();
            else if (subC == 2) allProfs.clear();
            else if (subC == 3) allAdmins.clear();
            else if (subC == 4) allCourses.clear();
        }
        else if (c == 7) {
            std::cout << "\ncollection<Person*> (polymorphic base class)\n";
            collection<Person*> demoPeople;

            Person* ps = new Student(201, "DemoAlex", "D001");
            Person* pp = new Professor(202, "DemoSmith", "Foreign");
            Person* pa = new Admin(203, "DemoAnna", "Admissions");

            demoPeople.add(ps);
            demoPeople.add(pp);
            demoPeople.add(pa);
            std::cout << "Size: " << demoPeople.getSize() << "\n";

            std::cout << "Get(0):\n";
            demoPeople.get(0)->printInfo();

            Person* found = demoPeople.findBy([](Person* P) { return P->getType() == "Professor"; });
            if (found) {
                std::cout << "FindBy type 'Professor':\n";
                found->printInfo();
            }

            demoPeople.remove(pp);
            std::cout << "After remove(professor): size = " << demoPeople.getSize() << "\n";

            demoPeople.print();

            demoPeople.clear();
            std::cout << "After clear: size = " << demoPeople.getSize() << "\n";

            delete ps; delete pp; delete pa;

            std::cout << "\ncollection<Course*>\n";
            collection<Course*> demoCourses;

            Course* c1 = new Course(301, "English", "A1", nullptr, "Mon 09:00", 10);
            Course* c2 = new Course(302, "English", "B2", nullptr, "Tue 09:00", 15);
            Course* c3 = new Course(303, "Deutsche", "A2", nullptr, "Wed 09:00", 20);

            demoCourses.add(c1);
            demoCourses.add(c2);
            demoCourses.add(c3);
            std::cout << "Size: " << demoCourses.getSize() << "\n";

            Course* b2 = demoCourses.findBy([](Course* C) { return C->getLevel() == "B2"; });
            if (b2) std::cout << "FindBy level 'B2': course id = " << b2->getId() << "\n";

            demoCourses.print();

            demoCourses.remove(c2);
            std::cout << "After remove(c2): size = " << demoCourses.getSize() << "\n";

            demoCourses.clear();
            std::cout << "After clear: size = " << demoCourses.getSize() << "\n";

            delete c1; delete c2; delete c3;
        }
        else if (c == 8) {
            std::cout << "\n1. Students\n2. Professors\n3. Admins\n4. Courses\n0. Back\n";
            subC = promptInt("Your choice: ");
            if (subC == 0) return;
            if (subC == 1) allStuds.print();
            else if (subC == 2) allProfs.print();
            else if (subC == 3) allAdmins.print();
            else if (subC == 4) allCourses.print();
        }
        else if (c == 9) printByLanguageLevel(allCourses);
        else std::cout << "Invalid\n";
    }
}

void printMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. All courses\n2. All students\n3. All professors\n4. All admins\n"
            "5. Course by id\n6. Student by id\n7. Professor by id\n8. Admin by id\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) { for (int i = 0; i < allCourses.getSize(); ++i) allCourses.get(i)->printInfo(); }
        else if (c == 2) { for (int i = 0; i < allStuds.getSize(); ++i) allStuds.get(i)->printInfo(); }
        else if (c == 3) { for (int i = 0; i < allProfs.getSize(); ++i) allProfs.get(i)->printInfo(); }
        else if (c == 4) { for (int i = 0; i < allAdmins.getSize(); ++i) allAdmins.get(i)->printInfo(); }
        else if (c == 5) { int id = promptInt("id: "); auto* C = allCourses.findBy([&](Course* c) { return c->getId() == id; }); if (C) C->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 6) { int id = promptInt("id: "); auto* S = allStuds.findBy([&](Student* s) { return s->getId() == id; }); if (S) S->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 7) { int id = promptInt("id: "); auto* P = allProfs.findBy([&](Professor* p) { return p->getId() == id; }); if (P) P->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 8) { int id = promptInt("id: "); auto* A = allAdmins.findBy([&](Admin* a) { return a->getId() == id; }); if (A) A->printInfo(); else std::cout << "Not found\n"; }
        else std::cout << "Invalid\n";
    }
}

void createMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Course\n2. Student\n3. Professor\n4. Admin\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) {
            int id = promptInt("Course id: ");
            auto lang = promptName("Language: ");
            auto lvl = promptName("Level: ");
            auto pn = promptName("Professor name: ");
            auto sch = promptName("Schedule: ");
            auto dep = promptName("Department: ");
            int mx = promptInt("Max capacity: ");

            Professor* P = allProfs.findBy([&](Professor* p) { return p->getName() == pn; });
            if (!P) {
                int pid = promptInt("Professor not found. New id: ");
                P = new Professor(pid, pn, dep);
                allProfs.add(P);
            }
            allCourses.add(new Course(id, lang, lvl, P, sch, mx));
            std::cout << "Course created!\n";
        }
        else if (c == 2) {
            int id = promptInt("Student id: ");
            auto name = promptName("Name: ");
            auto sid = promptName("Student ID: ");
            allStuds.add(new Student(id, name, sid));
            std::cout << "Student created!\n";
        }
        else if (c == 3) {
            int id = promptInt("Professor id: ");
            auto name = promptName("Name: ");
            auto dep = promptName("Department: ");
            allProfs.add(new Professor(id, name, dep));
            std::cout << "Professor created!\n";
        }
        else if (c == 4) {
            int id = promptInt("Admin id: ");
            auto name = promptName("Name: ");
            auto resp = promptName("Responsibility: ");
            allAdmins.add(new Admin(id, name, resp));
            std::cout << "Admin created!\n";
        }
        else std::cout << "Invalid\n";
    }
}

void deleteMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Delete course\n2. Delete student from course\n"
            "3. Remove professor from course\n4. Delete student\n"
            "5. Delete professor\n6. Delete admin\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        if (c == 1) {
            std::string lang = promptName("Course language: ");
            std::string lvl = promptName("Course level: ");
            Course* C = allCourses.findBy([&](Course* c) { return c->getLanguage() == lang && c->getLevel() == lvl; });
            if (!C) { std::cout << "Course not found...\n"; continue; }
            for (int i = 0; i < allStuds.getSize(); ++i) *allStuds.get(i) -= C;
            for (int i = 0; i < allProfs.getSize(); ++i) *allProfs.get(i) -= C;
            for (int i = 0; i < allAdmins.getSize(); ++i) *allAdmins.get(i) -= C;
            allCourses.remove(C);
            delete C;
            std::cout << "Course deleted!\n";
        }
        else if (c == 2) {
            int cid = promptInt("Course id: ");
            Course* C = allCourses.findBy([&](Course* c) { return c->getId() == cid; });
            if (!C) { std::cout << "Course not found...\n"; continue; }
            int sid = promptInt("Student id: ");
            Student* S = allStuds.findBy([&](Student* s) { return s->getId() == sid; });
            if (!S) { std::cout << "Student not found...\n"; continue; }
            *C -= S;
        }
        else if (c == 3) {
            int cid = promptInt("Course id: ");
            Course* C = allCourses.findBy([&](Course* c) { return c->getId() == cid; });
            if (!C) { std::cout << "Course not found...\n"; continue; }
            int pid = promptInt("Professor id: ");
            Professor* P = allProfs.findBy([&](Professor* p) { return p->getId() == pid; });
            if (!P) { std::cout << "Professor not found...\n"; continue; }
            *C -= P;
        }
        else if (c == 4) {
            int id = promptInt("Student id: ");
            Student* target = allStuds.findBy([&](Student* s) { return s->getId() == id; });
            if (!target) { std::cout << "Student not found...\n"; continue; }
            for (int i = 0; i < allCourses.getSize(); ++i) *allCourses.get(i) -= target;
            allStuds.remove(target);
            delete target;
            std::cout << "Deleted!\n";
        }
        else if (c == 5) {
            int id = promptInt("Professor id: ");
            Professor* target = allProfs.findBy([&](Professor* p) { return p->getId() == id; });
            if (!target) { std::cout << "Professor not found...\n"; continue; }
            for (int i = 0; i < allCourses.getSize(); ++i) *allCourses.get(i) -= target;
            allProfs.remove(target);
            delete target;
            std::cout << "Deleted!\n";
        }
        else if (c == 6) {
            int id = promptInt("Admin id: ");
            Admin* target = allAdmins.findBy([&](Admin* a) { return a->getId() == id; });
            if (!target) { std::cout << "Admin not found...\n"; continue; }
            allAdmins.remove(target);
            delete target;
            std::cout << "Deleted!\n";
        }
    }
}

void enrollMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Add student to course\n2. Add professor to course\n"
            "3. Add admin to course\n4. Remove student from course\n"
            "5. Remove professor from course\n6. Remove admin from course\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;
        if (c < 1 || c > 6) { std::cout << "Invalid\n"; continue; }

        int cid = promptInt("Course id: ");
        Course* C = allCourses.findBy([&](Course* c) { return c->getId() == cid; });
        if (!C) { std::cout << "Course not found...\n"; continue; }

        if (c == 1 || c == 4) {
            int sid = promptInt("Student id: ");
            Student* S = allStuds.findBy([&](Student* s) { return s->getId() == sid; });
            if (!S) { std::cout << "Student not found...\n"; continue; }

            if (c == 1) {
                int before = S->getCount();
                *S += C;
                if (S->getCount() > before) std::cout << "Student added!\n";
            }
            else *C -= S;
        }
        else if (c == 2 || c == 5) {
            int pid = promptInt("Professor id: ");
            Professor* P = allProfs.findBy([&](Professor* p) { return p->getId() == pid; });
            if (!P) { std::cout << "Professor not found...\n"; continue; }

            if (c == 2) {
                int before = P->getCount();
                *P += C;
                if (P->getCount() > before) std::cout << "Professor added!\n";
            }
            else *C -= P;
        }
        else {
            int aid = promptInt("Admin id: ");
            Admin* A = allAdmins.findBy([&](Admin* a) { return a->getId() == aid; });
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

void printByLanguageLevel(const collection<Course*>& allCourses) {
    if (allCourses.getSize() == 0) {
        std::cout << "\nNo courses...\n";
        return;
    }

    collection<std::string> languages;
    for (int i = 0; i < allCourses.getSize(); ++i) {
        const std::string& lang = allCourses.get(i)->getLanguage();
        if (languages.find(lang) == -1) languages.add(lang);
    }

    std::cout << "\nCourses grouped by language and level:\n";
    for (int i = 0; i < languages.getSize(); ++i) {
        const std::string lang = languages.get(i);
        std::cout << "\nLanguage: " << lang << "\n";

        collection<std::string> levels;
        for (int j = 0; j < allCourses.getSize(); ++j) {
            Course* C = allCourses.get(j);
            if (C->getLanguage() == lang && levels.find(C->getLevel()) == -1)
                levels.add(C->getLevel());
        }

        for (int k = 0; k < levels.getSize(); ++k) {
            const std::string lvl = levels.get(k);
            std::cout << "  Level " << lvl << ":\n";

            int count = 0;
            for (int m = 0; m < allCourses.getSize(); ++m) {
                Course* C = allCourses.get(m);
                if (C->getLanguage() == lang && C->getLevel() == lvl) {
                    std::cout << "    id:" << C->getId()
                        << ", schedule:" << C->getSchedule()
                        << ", students:" << C->getStudentCount()
                        << "/" << C->getMaxCount() << "\n";
                    ++count;
                }
            }
            std::cout << "    (" << count << " course(s))\n";
        }
    }
}