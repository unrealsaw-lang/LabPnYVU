#include "Menu.h"
#include "Course.h"
#include "Professor.h"
#include "Student.h"
#include "Admin.h"
#include "UniqueIdDuplicationException.h"
#include "InvalidDataException.h"
#include "InvalidOperationException.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <ctime>


template <typename T> static void addToCollection(std::unique_ptr<T> obj, collection<T*>& col) {
    if (!obj) throw MissingObjectException("Pointer to null");

    for (const auto& existing : col) {
        if (existing != nullptr && existing->getId() == obj->getId())
            throw UniqueIdDuplicationException("ID: " + std::to_string(obj->getId()) + " is already taken");
    }

    col.add(obj.release());
    std::cout << "\nSuccess!\n";
}
template <typename T> static void removeFromCollection(T* obj, collection<T*>& col) {
    if (obj) {
        col.remove(obj);
        std::cout << "\nSuccess!\n";
    }
}
template <typename T> static void getCollectionSize(const collection<T*>& col) {
    if (col.getSize() != 0) std::cout << "\nSize of the collection: " << col.getSize();
    else std::cout << "\nCollection is empty...";
}

template <typename T> static int promptUniqueId(const collection<T*>& col, const std::string& msg) {
    int id = promptInt(msg);
    for (const auto& existing : col) {
        if (existing != nullptr && existing->getId() == id) throw UniqueIdDuplicationException("ID: " + std::to_string(id) + " is already taken");
    }
    return id;
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

    while (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input error!\n";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return v;
}

static Course* findCourse(const collection<Course*>& allCourses) {
    while (true) {
        std::cout << "\n1. By id\n2. By language\n3. By level\n4. By schedule\n5. By student count\n6. By professor count\n7. By max count\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;
        try {
            if (c == 1) { 
                int id = promptInt("Enter id: "); 
                return allCourses.findBy([id](const Course* crs) { return crs->getId() == id; }); 
            }
            else if (c == 2) { 
                std::string sId = promptName("Enter language: "); 
                return allCourses.findBy([sId](const Course* crs) { return crs->getLanguage() == sId; }); 
            }
            else if (c == 3) { 
                std::string lvl = promptName("Enter level: "); 
                return allCourses.findBy([lvl](const Course* crs) { return crs->getLevel() == lvl; }); 
            }
            else if (c == 4) { 
                std::string sched = promptName("Enter schedule: "); 
                return allCourses.findBy([sched](const Course* crs) { return crs->getSchedule() == sched; }); 
            }
            else if (c == 5) { 
                int n = promptInt("Enter student count: "); 
                return allCourses.findBy([n](const Course* crs) { return crs->getStudentCount() == n; }); 
            }
            else if (c == 6) { 
                int n = promptInt("Enter professor count: "); 
                return allCourses.findBy([n](const Course* crs) { return crs->getProfessorCount() == n; }); 
            }
            else if (c == 7) { 
                int max = promptInt("Enter max count: "); 
                return allCourses.findBy([max](const Course* crs) { return crs->getMaxCount() == max; }); 
            }
        }
        catch (const MissingObjectException& E) { std::cout << "\n[Not found] " << E.what() << ". Try again\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Search error] " << E.what() << ". Try again\n"; }
    }
}
static Student* findStudent(const collection<Student*>& allStuds) {
    while (true) {
        std::cout << "\n1. By id\n2. By student id\n3. By name\n4. By course count\n5. By average grade\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;
        try {
            if (c == 1) { 
                int id = promptInt("Enter id: "); 
                return allStuds.findBy([id](const Student* stud) { return stud->getId() == id; }); 
            }
            else if (c == 2) { 
                std::string sId = promptName("Enter student id: "); 
                return allStuds.findBy([sId](const Student* stud) { return stud->getStudentId() == sId; }); 
            }
            else if (c == 3) { 
                std::string name = promptName("Enter name: "); 
                return allStuds.findBy([name](const Student* stud) { return stud->getName() == name; }); 
            }
            else if (c == 4) { 
                int n = promptInt("Enter course count: "); 
                return allStuds.findBy([n](const Student* stud) { return stud->getCount() == n; }); 
            }
            else if (c == 5) { 
                double avg = promptInt("Enter min average: "); 
                return allStuds.findBy([avg](const Student* stud) { return stud->calculateAverageMark() > avg; }); 
            }
        }
        catch (const MissingObjectException& E) { std::cout << "\n[Not found] " << E.what() << ". Try again\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Search error] " << E.what() << ". Try again\n"; }
    }
}
static Professor* findProfessor(const collection<Professor*>& allProfs) {
    while (true) {
        std::cout << "\n1. By id\n2. By department\n3. By name\n4. By course count\n5. By average rating\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;
        try {
            if (c == 1) { 
                int id = promptInt("Enter id: "); 
                return allProfs.findBy([id](const Professor* prof) { return prof->getId() == id; }); 
            }
            else if (c == 2) { 
                std::string dep = promptName("Enter department: "); 
                return allProfs.findBy([dep](const Professor* prof) { return prof->getDepartment() == dep; }); 
            }
            else if (c == 3) {
                std::string name = promptName("Enter name: "); 
                return allProfs.findBy([name](const Professor* prof) { return prof->getName() == name; }); 
            }
            else if (c == 4) { 
                int n = promptInt("Enter course count: "); 
                return allProfs.findBy([n](const Professor* prof) { return prof->getCount() == n; }); 
            }
            else if (c == 5) { 
                double avg = promptInt("Enter min average: "); 
                return allProfs.findBy([avg](const Professor* prof) { return prof->calculateAverageRating() > avg; }); 
            }
        }
        catch (const MissingObjectException& E) { std::cout << "\n[Not found] " << E.what() << ". Try again\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Search error] " << E.what() << ". Try again\n"; }
    }
}
static Admin* findAdmin(const collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. By id\n2. By responsibility\n3. By name\n4. By course count\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return nullptr;
        try {
            if (c == 1) { 
                int id = promptInt("Enter id: "); 
                return allAdmins.findBy([id](const Admin* adm) { return adm->getId() == id; }); 
            }
            else if (c == 2) { 
                std::string resp = promptName("Enter responsibility: "); 
                return allAdmins.findBy([resp](const Admin* adm) { return adm->getResponsibility() == resp; }); 
            }
            else if (c == 3) {
                std::string name = promptName("Enter name: ");
                return allAdmins.findBy([name](const Admin* adm) { return adm->getName() == name; }); 
            }
            else if (c == 4) { 
                int n = promptInt("Enter course count: "); 
                return allAdmins.findBy([n](const Admin* adm) { return adm->getCount() == n; }); 
            }
        }
        catch (const MissingObjectException& E) { std::cout << "\n[Not found] " << E.what() << ". Try again\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Search error] " << E.what() << ". Try again\n"; }
    }
}

void mainMenu(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Find object in collection\n2. Get object from collection\n3. Add object to collection\n4. Remove object from collection\n5. Get collection size\n6. Clear collection\n7. Print\n8. Enroll menu\n9. Grade/Rating menu\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;

        int subC;
        if (c == 1) {
            while (true) {
                std::cout << "\n1. Find student\n2. Find professor\n3. Find admin\n4. Find course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                if (subC == 1) { 
                    const auto* F = findStudent(allStuds); 
                    if (F) F->printInfo(); 
                }
                else if (subC == 2) { 
                    const auto* F = findProfessor(allProfs); 
                    if (F) F->printInfo(); 
                }
                else if (subC == 3) { 
                    const auto* F = findAdmin(allAdmins); 
                    if (F) F->printInfo();
                }
                else if (subC == 4) { 
                    const auto* F = findCourse(allCourses); 
                    if (F) F->printInfo(); 
                }
                else std::cout << "\nInvalid!";
            }
        }
        else if (c == 2) {
            while (true) {
                std::cout << "\n1. Get student\n2. Get professor\n3. Get admin\n4. Get course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                int idx = promptInt("Enter index: ");
                try {
                    if (subC == 1) { const auto* S = allStuds.get(idx); if (S) S->printInfo(); }
                    else if (subC == 2) { const auto* P = allProfs.get(idx); if (P) P->printInfo(); }
                    else if (subC == 3) { const auto* A = allAdmins.get(idx); if (A) A->printInfo(); }
                    else if (subC == 4) { const auto* C = allCourses.get(idx); if (C) C->printInfo(); }
                }
                catch (const CourseLimitViolationException& E) { std::cout << "\n[Index out of range] " << E.what() << "\n"; }
                catch (const LanguageSchoolException& E) { std::cout << "\n[Error] " << E.what() << "\n"; }
            }
        }
        else if (c == 3) {
            while (true) {
                std::cout << "\n1. Add student\n2. Add professor\n3. Add admin\n4. Add course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;

                try {
                    if (subC == 1) {
                        int id = promptUniqueId(allStuds, "Student id: ");
                        auto name = promptName("Name: ");
                        auto sid = promptName("Student ID: ");
                        addToCollection(std::make_unique<Student>(id, name, sid), allStuds);
                    }
                    else if (subC == 2) {
                        int id = promptUniqueId(allProfs, "Professor id: ");
                        auto name = promptName("Name: ");
                        auto dep = promptName("Department: ");
                        addToCollection(std::make_unique<Professor>(id, name, dep), allProfs);
                    }
                    else if (subC == 3) {
                        int id = promptUniqueId(allAdmins, "Admin id: ");
                        auto name = promptName("Name: ");
                        auto resp = promptName("Responsibility: ");
                        addToCollection(std::make_unique<Admin>(id, name, resp), allAdmins);
                    }
                    else if (subC == 4) {
                        int id = promptUniqueId(allCourses, "Course id: ");
                        auto lang = promptName("Language: ");
                        auto lvl = promptName("Level: ");
                        int pid = promptInt("Professor id: ");

                        Professor* P = nullptr;
                        try {
                            P = allProfs.findBy([pid](const Professor* refP) { return refP->getId() == pid; });
                        }
                        catch (const MissingObjectException&) {
                            std::cout << "\nProfessor not found. Create a new one\n";
                            pid = promptUniqueId(allProfs, "New professor id: ");
                            auto name = promptName("New professor name: ");
                            auto dep = promptName("New professor department: ");
                            auto newProf = std::make_unique<Professor>(pid, name, dep);
                            P = newProf.get();
                            addToCollection(std::move(newProf), allProfs);
                            std::cout << "\n";
                        }
                        auto sch = promptName("Schedule: ");
                        int mx = promptInt("Max capacity: ");
                        addToCollection(std::make_unique<Course>(id, lang, lvl, P, sch, mx), allCourses);
                    }
                }
                catch (const UniqueIdDuplicationException& E) { std::cout << "\n[Duplicate ID] " << E.what() << "\n"; }
                catch (const InvalidDataException& E) { std::cout << "\n[Invalid data] " << E.what() << "\n"; }
                catch (const MissingObjectException& E) { std::cout << "\n[Missing object] " << E.what() << "\n"; }
                catch (const CourseLimitViolationException& E) { std::cout << "\n[Limit exceeded] " << E.what() << "\n"; }
                catch (const InvalidOperationException& E) { std::cout << "\n[Invalid operation] " << E.what() << "\n"; }
                catch (const LanguageSchoolException& E) { std::cout << "\n[Error] " << E.what() << "\n"; }
            }
        }
        else if (c == 4) {
            while (true) {
                std::cout << "\n1. Remove student\n2. Remove professor\n3. Remove admin\n4. Remove course\n0. Back\n";
                subC = promptInt("Your choice: ");
                if (subC == 0) break;
                try {
                    if (subC == 1) { 
                        Student* S = findStudent(allStuds); 
                        if (S) removeFromCollection(S, allStuds); 
                    }
                    else if (subC == 2) { 
                        Professor* P = findProfessor(allProfs); 
                        if (P) removeFromCollection(P, allProfs); 
                    }
                    else if (subC == 3) { 
                        Admin* A = findAdmin(allAdmins); 
                        if (A) removeFromCollection(A, allAdmins); 
                    }
                    else if (subC == 4) { 
                        Course* C = findCourse(allCourses); 
                        if (C) removeFromCollection(C, allCourses); 
                    }
                }
                catch (const MissingObjectException& E) { std::cout << "\n[Missing object] " << E.what() << "\n"; }
                catch (const LanguageSchoolException& E) { std::cout << "\n[Error] " << E.what() << "\n"; }
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
        else if (c == 7) printMenu(allCourses, allStuds, allProfs, allAdmins);
        else if (c == 8) enrollMenu(allCourses, allStuds, allProfs, allAdmins);
        else if (c == 9) evaluationMenu(allCourses, allStuds, allProfs, allAdmins);
        else std::cout << "Invalid\n";
    }
}

void printMenu(const collection<Course*>& allCourses, const collection<Student*>& allStuds, const collection<Professor*>& allProfs, const collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. All courses\n2. All students\n3. All professors\n4. All admins\n5. Course by id\n6. Student by id\n7. Professor by id\n8. Admin by id\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;
        try {
            if (c == 1) { for (const auto& crs : allCourses) crs->printInfo(); }
            else if (c == 2) { for (const auto& stud : allStuds) stud->printInfo(); }
            else if (c == 3) { for (const auto& prof : allProfs) prof->printInfo(); }
            else if (c == 4) { for (const auto& adm : allAdmins) adm->printInfo(); }
            else if (c == 5) { 
                int id = promptInt("id: "); 
                const auto* C = allCourses.findBy([id](const Course* crs) { return crs->getId() == id; });
                if (C) C->printInfo(); 
            }
            else if (c == 6) { 
                int id = promptInt("id: "); 
                const auto* S = allStuds.findBy([id](const Student* stud) { return stud->getId() == id; }); 
                if (S) S->printInfo(); 
            }
            else if (c == 7) { 
                int id = promptInt("id: "); 
                const auto* P = allProfs.findBy([id](const Professor* prof) { return prof->getId() == id; }); 
                if (P) P->printInfo(); 
            }
            else if (c == 8) { 
                int id = promptInt("id: "); 
                const auto* A = allAdmins.findBy([id](const Admin* adm) { return adm->getId() == id; }); 
                if (A) A->printInfo(); 
            }
        }
        catch (const MissingObjectException& E) { std::cout << "\n[Missing object] " << E.what() << "\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Error] " << E.what() << "\n"; }
    }
}

void enrollMenu(const collection<Course*>& allCourses, const collection<Student*>& allStuds, const collection<Professor*>& allProfs, const collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Add student to course\n2. Add professor to course\n3. Add admin to course\n4. Remove student from course\n5. Remove professor from course\n6. Remove admin from course\n0. Back\n";
        int c = promptInt("Your choice: ");
        if (c == 0) return;
        if (c < 1 || c > 6) { std::cout << "Invalid\n"; continue; }

        try {
            int cid = promptInt("Course id: ");
            Course* C = allCourses.findBy([cid](const Course* crs) { return crs->getId() == cid; });

            if (c == 1 || c == 4) {
                int sid = promptInt("Student id: ");
                Student* S = allStuds.findBy([sid](const Student* stud) { return stud->getId() == sid; });
                if (c == 1) { 
                    int before = S->getCount(); 
                    *S += C; 
                    if (S->getCount() > before) std::cout << "Student added!\n"; 
                }
                else *C -= S;
            }
            else if (c == 2 || c == 5) {
                int pid = promptInt("Professor id: ");
                Professor* P = allProfs.findBy([pid](const Professor* prof) { return prof->getId() == pid; });
                if (c == 2) { 
                    int before = P->getCount(); 
                    *P += C; 
                    if (P->getCount() > before) std::cout << "Professor added!\n"; 
                }
                else *C -= P;
            }
            else {
                int aid = promptInt("Admin id: ");
                Admin* A = allAdmins.findBy([aid](const Admin* adm) { return adm->getId() == aid; });
                if (c == 3) { 
                    int before = A->getCount(); *A += C; 
                    if (A->getCount() > before) std::cout << "Admin added!\n"; 
                }
                else { 
                    int before = A->getCount(); 
                    *A -= C; if (A->getCount() < before) std::cout << "Admin removed!\n"; }
            }
        }
        catch (const CourseLimitViolationException& E) { std::cout << "\n[Limit exceeded] " << E.what() << "\n"; }
        catch (const InvalidOperationException& E) { std::cout << "\n[Invalid operation] " << E.what() << "\n"; }
        catch (const MissingObjectException& E) { std::cout << "\n[Missing object] " << E.what() << "\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Error] " << E.what() << "\n"; }
    }
}

void evaluationMenu(const collection<Course*>& allCourses, const collection<Student*>& allStuds, const collection<Professor*>& allProfs, const collection<Admin*>& allAdmins) {
    while (true) {
        std::cout << "\n1. Add mark to student\n";
        std::cout << "2. Add rating to professor\n";
        std::cout << "0. Back\n";

        int c = promptInt("Your choice: ");
        if (c == 0) return;

        try {
            if (c == 1) {
                int sid = promptInt("Enter student id: ");
                Student* S = allStuds.findBy([sid](const Student* stud) { return stud->getId() == sid; });

                int mark = promptInt("Enter mark: ");
                S->addMark(mark);

                std::cout << "\nSuccess! Mark " << mark << " added to " << S->getName() << ".\n";
                std::cout << "Current average mark: " << S->calculateAverageMark() << "\n";
            }
            else if (c == 2) {
                int pid = promptInt("Enter professor id: ");
                Professor* P = allProfs.findBy([pid](const Professor* prof) { return prof->getId() == pid; });

                int rating = promptInt("Enter rating: ");
                P->rate(rating);

                std::cout << "\nSuccess! Rating " << rating << " added to Professor " << P->getName() << ".\n";
                std::cout << "Current average rating: " << P->calculateAverageRating() << "\n";
            }
            else std::cout << "Invalid choice!\n";
        }
        catch (const MissingObjectException& E) { std::cout << "\n[Not found] " << E.what() << "\n"; }
        catch (const InvalidOperationException& E) { std::cout << "\n[Invalid operation] " << E.what() << "\n"; }
        catch (const LanguageSchoolException& E) { std::cout << "\n[Error] " << E.what() << "\n"; }
    }
}