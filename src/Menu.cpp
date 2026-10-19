#include "Menu.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include "Collection.h"
#include <iostream>

template <typename T, typename F> T findBy(std::vector<T>& vec, F condition) {
    for (const T& item : vec) {
        if (condition(item)) return item;
    }
    return T();
}
template <typename T> static void addToCollection(T* obj, collection<T*>& col) {
    if (obj) { col.add(obj); std::cout << "\nSuccess!"; }
    else std::cout << "\nNull!";
}
template <typename T> static void removeFromCollection(T* obj, collection<T*>& col) {
    if (obj) { col.remove(obj); std::cout << "\nSucces!"; }
    else std::cout << "\nNull!";
}
template <typename T> static void getCollectionSize(collection<T*>& col) {
    if (col.getSize() != 0) std::cout << "\nSize of the collection: " << col.getSize();
    else std::cout << "\nCollection is empty...";
}

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

Course* findCourseById(const std::vector<Course*>& allCourses, int id) {
    for (Course* C : allCourses) if (C->getId() == id) return C;
    return nullptr;
}
Student* findStudentById(const std::vector<Student*>& allStuds, int id) {
    for (Student* S : allStuds) if (S->getId() == id) return S;
    return nullptr;
}
Professor* findProfessorById(const std::vector<Professor*>& allProfs, int id) {
    for (Professor* P : allProfs) if (P->getId() == id) return P;
    return nullptr;
}
Admin* findAdminById(const std::vector<Admin*>& allAdmins, int id) {
    for (Admin* A : allAdmins) if (A->getId() == id) return A;
    return nullptr;
}
Student* findStudentByName(const std::vector<Student*>& allStuds, const std::string& name) {
    for (Student* S : allStuds) if (S->getName() == name) return S;
    return nullptr;
}
Professor* findProfessorByName(const std::vector<Professor*>& allProfs, const std::string& name) {
    for (Professor* P : allProfs) if (P->getName() == name) return P;
    return nullptr;
}
Course* findCourseByTitle(const std::vector<Course*>& allCourses) {
    std::string lvl, lang;
    std::cout << "Course language: "; std::cin >> lang;
    std::cout << "Course level: ";    std::cin >> lvl;
    std::cin.ignore();
    for (Course* C : allCourses)
    if (C->getLanguage() == lang && C->getLevel() == lvl) return C;
    return nullptr;
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

static Course* findCourse(const collection<Course*> allCourses) {
    while (true) {
        std::cout << "\n1. By id\n";
        std::cout << "2. By language\n";
        std::cout << "3. By level\n";
        std::cout << "4. By schdeule\n";
        std::cout << "5. By student count\n";
        std::cout << "6. By professor count\n";
        std::cout << "7. By max count\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Course* found = nullptr;
        if (c == 1) {
            int id = promptInt("Enter id: ");
            found = allCourses.findBy([&](Course* C) { return C->getId() == id; });
        }
        if (c == 2) {
            std::string lang = promptName("Enter language: ");
            found = allCourses.findBy([&](Course* C) { return C->getLanguage() == lang; });
        }
        if (c == 3) {
            std::string lvl = promptName("Enter level: ");
            found = allCourses.findBy([&](Course* C) { return C->getLevel() == lvl; });
        }if (c == 4) {
            std::string sched = promptName("Enter schedule: ");
            found = allCourses.findBy([&](Course* C) { return C->getSchedule() == sched; });
        }
        if (c == 5) {
            int sCount = promptInt("Enter course count: ");
            found = allCourses.findBy([&](Course* C) { return C->getStudentCount() == sCount; });
        }
        if (c == 6) {
            int pCount = promptInt("Enter professor count: ");
            found = allCourses.findBy([&](Course* C) { return C->getProfessorCount() == pCount; });
        }
        if (c == 7) {
            int max = promptInt("Enter max count: ");
            found = allCourses.findBy([&](Course* C) { return C->getMaxCount() == max; });
        }

        if (found) return found;
        else std::cout << "\nNot found\n";

    }
}
static Student* findStudent(const collection<Student*>& allStuds) {
    while (true) {
        std::cout << "\n1. By id\n";
        std::cout << "2. By student id\n";
        std::cout << "3. By name\n";
        std::cout << "4. By course count\n";
        std::cout << "5. By average grade\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Student* found = nullptr;
        if (c == 1) {
            int id = promptInt("Enter id: ");
            found = allStuds.findBy([&](Student* S) { return S->getId() == id; });
        }
        if (c == 2) {
            std::string sId = promptName("Enter student id: ");
            found = allStuds.findBy([&](Student* S) { return S->getStudentId() == sId; });
        }
        if (c == 3) {
            std::string n = promptName("Enter student name: ");
            found = allStuds.findBy([&](Student* S) { return S->getName() == n; });
        }
        if (c == 4) {
            int count = promptInt("Enter course count: ");
            found = allStuds.findBy([&](Student* S) { return S->getCount() == count; });
        }
        if (c == 5) {
            double avg = promptInt("Enter min average grade: ");
            found = allStuds.findBy([&](Student* S) { return S->calculateAverageMark() > avg; });
        }

        if (found) {
            std::cout << "\nFound:\n";
            return found;
        }
        else std::cout << "\nNot found\n";

    }
}
static Professor* findProfessor(const collection<Professor*>& allProfs) {
    while (true) {
        std::cout << "\n1. By id\n";
        std::cout << "2. By department\n";
        std::cout << "3. By name\n";
        std::cout << "4. By course count\n";
        std::cout << "5. By average rating\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Professor* found = nullptr;
        if (c == 1) {
            int id = promptInt("Enter id: ");
            found = allProfs.findBy([&](Professor* P) { return P->getId() == id; });
        }
        if (c == 2) {
            std::string dep = promptName("Enter professor department: ");
            found = allProfs.findBy([&](Professor* P) { return P->getDepartment() == dep; });
        }
        if (c == 3) {
            std::string n = promptName("Enter professor name: ");
            found = allProfs.findBy([&](Professor* P) { return P->getName() == n; });
        }
        if (c == 4) {
            int count = promptInt("Enter course count: ");
            found = allProfs.findBy([&](Professor* P) { return P->getCount() == count; });
        }
        if (c == 5) {
            double avg = promptInt("Enter min average rating: ");
            found = allProfs.findBy([&](Professor* P) { return P->calculateAverageRating() > avg; });
        }

        if (found) {
            std::cout << "\nFound:\n";
            return found;
        }
        else std::cout << "\nNot found\n";

    }
}
static Admin* findAdmin(const collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. By id\n";
        std::cout << "2. By responsibility\n";
        std::cout << "3. By name\n";
        std::cout << "4. By course count\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;

        Admin* found = nullptr;
        if (c == 1) {
            int id = promptInt("Enter id: ");
            found = allAdmins.findBy([&](Admin* A) { return A->getId() == id; });
        }
        if (c == 2) {
            std::string resp = promptName("Enter admin responsibility: ");
            found = allAdmins.findBy([&](Admin* A) { return A->getResponsibility() == resp; });
        }
        if (c == 3) {
            std::string n = promptName("Enter professor name: ");
            found = allAdmins.findBy([&](Admin* A) { return A->getName() == n; });
        }
        if (c == 4) {
            int count = promptInt("Enter course count: ");
            found = allAdmins.findBy([&](Admin* A) { return A->getCount() == count; });
        }

        if (found) {
            std::cout << "\nFound:\n";
            return found;
        }
        else std::cout << "\nNot found\n";

    }
}

void templatesMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Find object to the collection\n";
        std::cout << "2. Get object from the collection\n";
        std::cout << "3. Add object to the collection\n";
        std::cout << "4. Remove object from the collection\n";
        std::cout << "5. Get collection size\n";
        std::cout << "6. Clear collection\n";
        std::cout << "7. Demo with different data types\n";
        std::cout << "8. Print\n";
        std::cout << "0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        int subC;
        if (c == 1) {
            while (true) {
            std::cout << "\n1. Find student\n";
            std::cout << "2. Find professor\n";
            std::cout << "3. Find admin\n";
            std::cout << "4. Find course\n";
            std::cout << "0. Back\n";

            subC = promptInt("Your choice: ");

            if (subC == 1) {
                Student* found = findStudent(allStuds);
                if (found) found->printInfo();
            }
            else if (subC == 2) {
                Professor* found = findProfessor(allProfs);
                if (found) found->printInfo();
            }
            else if (subC == 3) {
                Admin* found = findAdmin(allAdmins);
                if (found) found->printInfo();
            }
            else if (subC == 4) {
                Course* found = findCourse(allCourses);
                if (found) found->printInfo();
            }
            else if (subC == 0) break;
            else std::cout << "\nInvalid!";
            }
        }
        else if (c == 2) {
            while (true) {
                std::cout << "\n1. Get student\n";
                std::cout << "2. Get professor\n";
                std::cout << "3. Get admin\n";
                std::cout << "4. Get course\n";
                std::cout << "0. Back\n";

                subC = promptInt("Your choice: ");

                if (subC == 0) break;

                if (subC < 1 || subC > 4) {
                    std::cout << "\nInvalid!\n";
                    continue;
                }

                int index = promptInt("Enter index: ");
                if (subC == 1) {
                    Student* S = allStuds.get(index);
                    if (S) S->printInfo();
                }
                else if (subC == 2) {
                    Professor* P = allProfs.get(index);
                    if (P) P->printInfo();
                }
                else if (subC == 3) {
                    Admin* A = allAdmins.get(index);
                    if (A) A->printInfo();
                }
                else if (subC == 4) {
                    Course* C = allCourses.get(index);
                    if (C) C->printInfo();
                }
            }
        }
        else if (c == 3) {
            while (true) {
                std::cout << "\n1. Add student\n";
                std::cout << "2. Add professor\n";
                std::cout << "3. Add admin\n";
                std::cout << "4. Add course\n";
                std::cout << "0. Back\n";

                subC = promptInt("Your choice: ");
                if (subC == 0) break;

                if (subC == 1) {
                    int id = promptInt("Student id: ");
                    std::string name = promptName("Name: ");
                    std::string sId = promptName("Student ID: ");
                    Student* newStudent = new Student(id, name, sId);
                    addToCollection(newStudent, allStuds);
                }
                else if (subC == 2) {
                    int id = promptInt("Professor id: ");
                    std::string name = promptName("Name: ");
                    std::string dep = promptName("Department: ");
                    Professor* newProfessor = new Professor(id, name, dep);
                    addToCollection(newProfessor, allProfs);
                }
                else if (subC == 3) {
                    int id = promptInt("Admin id: ");
                    std::string name = promptName("Name: ");
                    std::string resp = promptName("Responsibility: ");
                    Admin* newAdmin = new Admin(id, name, resp);
                    addToCollection(newAdmin, allAdmins);
                }
                else if (subC == 4) {
                    int id = promptInt("Course id: ");
                    std::string lang = promptName("Language: ");
                    std::string lvl = promptName("Level: ");
                    std::string pname = promptName("Professor name: ");
                    std::string sched = promptName("Schedule: ");
                    int max = promptInt("Max capacity: ");

                    Professor* P = allProfs.findBy([&](Professor* p) { return p->getName() == pname; });

                    if (!P) {
                        int pid = promptInt("Professor not found. Enter new professor id: ");
                        std::string dep = promptName("Department: ");
                        P = new Professor(pid, pname, dep);
                        addToCollection(P, allProfs);
                    }

                    Course* newCourse = new Course(id, lang, lvl, P, sched, max);
                    addToCollection(newCourse, allCourses);
                }
                else std::cout << "\nInvalid!\n";
            }
        }
        else if (c == 4) {
            while (true) {
                std::cout << "\n1. Remove student\n";
                std::cout << "2. Remove professor\n";
                std::cout << "3. Remove admin\n";
                std::cout << "4. Remove course\n";
                std::cout << "0. Back\n";

                subC = promptInt("Your choice: ");

                if (subC == 1) removeFromCollection(findStudent(allStuds), allStuds);
                else if (subC == 2) removeFromCollection(findProfessor(allProfs), allProfs);
                else if (subC == 3) removeFromCollection(findAdmin(allAdmins), allAdmins);
                else if (subC == 4) removeFromCollection(findCourse(allCourses), allCourses);
                else if (subC == 0) break;
                else std::cout << "\nInvalid!";
            }
        }
        else if (c == 5) {
            while (true) {
                std::cout << "\n1. Get students size\n";
                std::cout << "2. Get professors size\n";
                std::cout << "3. Get admins size\n";
                std::cout << "4. Get courses size\n";
                std::cout << "0. Back\n";

                subC = promptInt("Your choice: ");
                if (subC == 1) getCollectionSize(allStuds);
                else if (subC == 2) getCollectionSize(allProfs);
                else if (subC == 3) getCollectionSize(allAdmins);
                else if (subC == 4) getCollectionSize(allCourses);
                else if (subC == 0) break;
                else std::cout << "\nInvalid!";
            }
        }
        else if (c == 6) {
            while (true) {
                std::cout << "\n1. Clear students\n";
                std::cout << "2. Clear professors\n";
                std::cout << "3. Clear admins\n";
                std::cout << "4. Clear courses\n";
                std::cout << "0. Back\n";

                subC = promptInt("Your choice: ");
                if (subC == 1) allStuds.clear();
                else if (subC == 2) allProfs.clear();
                else if (subC == 3) allAdmins.clear();
                else if (subC == 4) allCourses.clear();
                else if (subC == 0) break;
                else std::cout << "\nInvalid!";
            }
        }
        else if (c == 7) {
            std::cout << "\nInt collection: \n";
            collection<int> nums;
            nums.add(10);
            nums.add(20);
            nums.add(30);
            nums.print();

            std::cout << "Size: " << nums.getSize() << "\n";
            std::cout << "Get(1): " << nums.get(1) << "\n";
            std::cout << "Find(20): " << nums.find(20) << "\n";
            std::cout << "FindBy(>15): " << nums.findBy([](int x) { return x > 15; }) << "\n";
            nums.remove(20);
            std::cout << "After remove(20): size = " << nums.getSize() << "\n";
            nums.clear();
            std::cout << "After clear: size = " << nums.getSize() << "\n";

            std::cout << "\nString collection: \n";
            collection<std::string> words;
            words.add("String1");
            words.add("STRING");
            words.add("str3");
            words.print();

            std::cout << "Size: " << words.getSize() << "\n";
            std::cout << "FindBy(len>6): " << words.findBy([](const std::string& s) {
                return s.size() > 6;
                }) << "\n";
        }
        else if (c == 8) {
            while (true) {
                std::cout << "\n1. Students\n";
                std::cout << "2. Professors\n";
                std::cout << "3. Admins\n";
                std::cout << "4. Courses\n";
                std::cout << "0. Back\n";
                int subC = promptInt("Your choice: ");
                if (subC == 0) return;

                if (subC == 1) allStuds.print();
                else if (subC == 2) allProfs.print();
                else if (subC == 3) allAdmins.print();
                else if (subC == 4) allCourses.print();
                else std::cout << "Invalid\n";
            }
        }
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

        if (c == 1) { for (Course* C : allCourses) C->printInfo(); }
        else if (c == 2) { for (Student* S : allStuds) S->printInfo(); }
        else if (c == 3) { for (Professor* P : allProfs) P->printInfo(); }
        else if (c == 4) { for (Admin* A : allAdmins) A->printInfo(); }
        else if (c == 5) { int id = promptInt("id: "); Course* C = findCourseById(allCourses, id); if (C) C->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 6) { int id = promptInt("id: "); Student* S = findStudentById(allStuds, id); if (S) S->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 7) { int id = promptInt("id: "); Professor* P = findProfessorById(allProfs, id); if (P) P->printInfo(); else std::cout << "Not found\n"; }
        else if (c == 8) { int id = promptInt("id: "); Admin* A = findAdminById(allAdmins, id); if (A) A->printInfo(); else std::cout << "Not found\n"; }
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