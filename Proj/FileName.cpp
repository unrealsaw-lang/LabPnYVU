#include <iostream>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

class Professor;
class Student;

struct Schedule {
    char* day;
    char* time;
};

class Course {
    Student* studs[30];
    int maxcount;
    int currcount;
    Professor* prof;
    char* level;
    char* language;
    Schedule schedule;

public:
    Course(const char* lang, const char* lvl, Professor* P,
        const char* day, const char* time, int max);
    ~Course();

    void setCourseLevel(const char* lvl);
    void setCourseLanguage(const char* lang);
    void setCourseDay(const char* d);
    void setCourseTime(const char* t);

    const char* getCourseLevel() const;
    const char* getCourseLanguage() const;
    const char* getCourseDay() const;
    const char* getCourseTime() const;
    int getCourseCurrCount() const;
    int getCourseMaxCount() const;
    Professor* getProfessor() const;

    bool addStudent(Student* s);
    bool removeStudent(Student* s);
    void printCourse() const;
};

class Professor {
    Course* courses[10];
    int coursecount;
    char* name;

public:
    Professor(const char* N);
    ~Professor();

    int AddCourse(Course* C);
    void setName(const char* N);
    const char* getname() const;
    int getcoursecount() const;
    void printInfo() const;
    void printCourses() const;
};

class Student {
    Course* courses[10];
    int coursecount;
    char* name;

public:
    Student(const char* N);
    ~Student();

    void setName(const char* N);
    const char* getname() const;
    int getcoursecount() const;

    bool addCourse(Course* c);
    bool removeCourse(Course* c);
    void printInfo() const;
};

Course::Course(const char* lang, const char* lvl, Professor* P,
    const char* day, const char* time, int max) {
    language = new char[strlen(lang) + 1];
    strcpy(language, lang);
    level = new char[strlen(lvl) + 1];
    strcpy(level, lvl);
    maxcount = max;
    currcount = 0;
    for (int i = 0; i < 30; i++) studs[i] = nullptr;
    prof = P;
    schedule.day = new char[strlen(day) + 1];
    strcpy(schedule.day, day);
    schedule.time = new char[strlen(time) + 1];
    strcpy(schedule.time, time);
    cout << language << " course created!\n";
}

Course::~Course() {
    delete[] language;
    delete[] level;
    delete[] schedule.day;
    delete[] schedule.time;
}

void Course::setCourseLevel(const char* lvl) {
    delete[] level;
    level = new char[strlen(lvl) + 1];
    strcpy(level, lvl);
}

void Course::setCourseLanguage(const char* lang) {
    delete[] language;
    language = new char[strlen(lang) + 1];
    strcpy(language, lang);
}

void Course::setCourseDay(const char* d) {
    delete[] schedule.day;
    schedule.day = new char[strlen(d) + 1];
    strcpy(schedule.day, d);
}

void Course::setCourseTime(const char* t) {
    delete[] schedule.time;
    schedule.time = new char[strlen(t) + 1];
    strcpy(schedule.time, t);
}

const char* Course::getCourseLevel() const { return level; }
const char* Course::getCourseLanguage() const { return language; }
const char* Course::getCourseDay() const { return schedule.day; }
const char* Course::getCourseTime() const { return schedule.time; }
int Course::getCourseCurrCount() const { return currcount; }
int Course::getCourseMaxCount() const { return maxcount; }
Professor* Course::getProfessor() const { return prof; }

bool Course::addStudent(Student* s) {
    if (currcount >= maxcount) {
        cout << "Course is full (max " << maxcount << " students)!\n";
        return false;
    }
    for (int i = 0; i < currcount; i++) {
        if (studs[i] == s) {
            cout << "Student already added\n";
            return false;
        }
    }
    studs[currcount++] = s;
    return true;
}

bool Course::removeStudent(Student* s) {
    for (int i = 0; i < currcount; i++) {
        if (studs[i] == s) {
            for (int j = i; j < currcount - 1; j++)
                studs[j] = studs[j + 1];
            studs[--currcount] = nullptr;
            return true;
        }
    }
    return false;
}

void Course::printCourse() const {
    cout << "Language: " << language << "\n";
    cout << "Level: " << level << "\n";
    cout << "Professor: " << (prof ? prof->getname() : "none") << "\n";
    cout << "Schedule: " << schedule.day << " " << schedule.time << "\n";
    cout << "Students: " << currcount << "/" << maxcount << "\n";
    if (currcount > 0) {
        cout << "Enrolled: ";
        for (int i = 0; i < currcount; i++)
            cout << studs[i]->getname() << " ";
        cout << "\n";
    }
    cout << "\n";
}

Professor::Professor(const char* N) {
    name = new char[strlen(N) + 1];
    strcpy(name, N);
    coursecount = 0;
    for (int i = 0; i < 10; i++) courses[i] = nullptr;
}

Professor::~Professor() {
    delete[] name;
}

int Professor::AddCourse(Course* C) {
    if (coursecount < 10) {
        courses[coursecount++] = C;
        return 1;
    }
    return 0;
}

void Professor::setName(const char* N) {
    delete[] name;
    name = new char[strlen(N) + 1];
    strcpy(name, N);
}

const char* Professor::getname() const { return name; }
int Professor::getcoursecount() const { return coursecount; }

void Professor::printInfo() const {
    cout << "Professor: " << name << "\n";
    cout << "Number of courses: " << coursecount << "\n";
    if (coursecount == 0) cout << "  (no courses)\n";
    else {
        cout << "  Teaches:\n";
        for (int i = 0; i < coursecount; i++) {
            cout << "   - " << courses[i]->getCourseLanguage()
                << " (" << courses[i]->getCourseLevel() << ")\n";
        }
    }
    cout << "\n";
}

void Professor::printCourses() const {
    cout << "Professor " << name << " teaches:\n";
    if (coursecount == 0) cout << "no courses!\n";
    else {
        for (int i = 0; i < coursecount; i++) {
            cout << " - " << courses[i]->getCourseLanguage()
                << " (" << courses[i]->getCourseLevel() << "), "
                << courses[i]->getCourseDay() << " "
                << courses[i]->getCourseTime() << "\n";
        }
    }
}

Student::Student(const char* N) {
    name = new char[strlen(N) + 1];
    strcpy(name, N);
    coursecount = 0;
    for (int i = 0; i < 10; i++) courses[i] = nullptr;
}

Student::~Student() {
    delete[] name;
}

void Student::setName(const char* N) {
    delete[] name;
    name = new char[strlen(N) + 1];
    strcpy(name, N);
}

const char* Student::getname() const { return name; }
int Student::getcoursecount() const { return coursecount; }

bool Student::addCourse(Course* c) {
    if (coursecount >= 10) {
        cout << "Student can't take more than 10 courses.\n";
        return false;
    }
    for (int i = 0; i < coursecount; i++) {
        if (courses[i] == c) {
            cout << "Already in this course\n";
            return false;
        }
    }
    if (!c->addStudent(this)) return false;
    courses[coursecount++] = c;
    return true;
}

bool Student::removeCourse(Course* c) {
    for (int i = 0; i < coursecount; i++) {
        if (courses[i] == c) {
            for (int j = i; j < coursecount - 1; j++)
                courses[j] = courses[j + 1];
            courses[--coursecount] = nullptr;
            c->removeStudent(this);
            return true;
        }
    }
    return false;
}

void Student::printInfo() const {
    cout << "Student: " << name << "\n";
    cout << "Enrolled in " << coursecount << " course(s):\n";
    if (coursecount == 0) cout << "  (no courses)\n";
    else {
        for (int i = 0; i < coursecount; i++) {
            cout << "   - " << courses[i]->getCourseLanguage()
                << " (" << courses[i]->getCourseLevel() << "), "
                << courses[i]->getCourseDay() << " "
                << courses[i]->getCourseTime() << "\n";
        }
    }
    cout << "\n";
}

struct ProfessorsData {
    Professor** data;
    int size;
};

struct CoursesData {
    Course** data;
    int size;
};

ProfessorsData profList = { nullptr, 0 };
CoursesData courseList = { nullptr, 0 };
Student* students[100];
int studentCount = 0;

void addProfessor() {
    char name[100];
    cout << "Enter professor name: ";
    cin.ignore();
    cin.getline(name, 100);

    for (int i = 0; i < profList.size; i++) {
        if (strcmp(profList.data[i]->getname(), name) == 0) {
            cout << "Professor already exists!\n";
            return;
        }
    }

    Professor** newData = new Professor * [profList.size + 1];
    for (int i = 0; i < profList.size; i++)
        newData[i] = profList.data[i];
    newData[profList.size] = new Professor(name);
    delete[] profList.data;
    profList.data = newData;
    profList.size++;
    cout << "Professor added\n";
}

void addCourse() {
    if (profList.size == 0) {
        cout << "Create a professor first.\n";
        return;
    }

    char lang[50], lvl[20], day[20], time[20], profName[100];
    int max;
    cout << "Language: ";
    cin.ignore();
    cin.getline(lang, 50);
    cout << "Level: ";
    cin.getline(lvl, 20);
    cout << "Professor name: ";
    cin.getline(profName, 100);
    cout << "Max students: ";
    cin >> max;
    cin.ignore();
    cout << "Day: ";
    cin.getline(day, 20);
    cout << "Time: ";
    cin.getline(time, 20);

    Professor* prof = nullptr;
    for (int i = 0; i < profList.size; i++) {
        if (strcmp(profList.data[i]->getname(), profName) == 0) {
            prof = profList.data[i];
            break;
        }
    }
    if (!prof) {
        cout << "Professor not found\n";
        return;
    }

    Course* c = new Course(lang, lvl, prof, day, time, max);
    if (!prof->AddCourse(c)) {
        cout << "Professor has too many courses (max 10)\n";
        delete c;
        return;
    }

    Course** newData = new Course * [courseList.size + 1];
    for (int i = 0; i < courseList.size; i++)
        newData[i] = courseList.data[i];
    newData[courseList.size] = c;
    delete[] courseList.data;
    courseList.data = newData;
    courseList.size++;
    cout << "Course created!\n";
}

void addStudent() {
    char name[100];
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(name, 100);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i]->getname(), name) == 0) {
            cout << "Student already exists\n";
            return;
        }
    }

    students[studentCount++] = new Student(name);
    cout << "Student added\n";
}

void enrollStudent() {
    if (studentCount == 0 || courseList.size == 0) {
        cout << "Need both students and courses\n";
        return;
    }

    char sname[100], lang[50];
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(sname, 100);
    cout << "Enter course language: ";
    cin.getline(lang, 50);

    Student* s = nullptr;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i]->getname(), sname) == 0) {
            s = students[i];
            break;
        }
    }
    if (!s) {
        cout << "Student not found\n";
        return;
    }

    Course* c = nullptr;
    for (int i = 0; i < courseList.size; i++) {
        if (strcmp(courseList.data[i]->getCourseLanguage(), lang) == 0) {
            c = courseList.data[i];
            break;
        }
    }
    if (!c) {
        cout << "Course not found\n";
        return;
    }

    if (s->addCourse(c))
        cout << "Success\n";
    else
        cout << "Fail\n";
}

void unenrollStudent() {
    if (studentCount == 0 || courseList.size == 0) {
        cout << "Need both students and courses\n";
        return;
    }

    char sname[100], lang[50];
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(sname, 100);
    cout << "Enter course language: ";
    cin.getline(lang, 50);

    Student* s = nullptr;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i]->getname(), sname) == 0) {
            s = students[i];
            break;
        }
    }
    if (!s) {
        cout << "Student not found\n";
        return;
    }

    Course* c = nullptr;
    for (int i = 0; i < courseList.size; i++) {
        if (strcmp(courseList.data[i]->getCourseLanguage(), lang) == 0) {
            c = courseList.data[i];
            break;
        }
    }
    if (!c) {
        cout << "Course not found\n";
        return;
    }

    if (s->removeCourse(c))
        cout << "Student removed from course\n";
    else
        cout << "Fail\n";
}

void changeCourseSchedule() {
    if (courseList.size == 0) {
        cout << "No courses\n";
        return;
    }

    char lang[50], newDay[20], newTime[20];
    cout << "Enter course language: ";
    cin.ignore();
    cin.getline(lang, 50);

    Course* c = nullptr;
    for (int i = 0; i < courseList.size; i++) {
        if (strcmp(courseList.data[i]->getCourseLanguage(), lang) == 0) {
            c = courseList.data[i];
            break;
        }
    }
    if (!c) {
        cout << "Course not found\n";
        return;
    }

    cout << "Current schedule: " << c->getCourseDay() << " " << c->getCourseTime() << "\n";
    cout << "Enter new day: ";
    cin.getline(newDay, 20);
    cout << "Enter new time: ";
    cin.getline(newTime, 20);
    c->setCourseDay(newDay);
    c->setCourseTime(newTime);
    cout << "Schedule updated\n";
}

void showAllProfessors() {
    cout << "\n     ALL PROFESSORS      \n";
    if (profList.size == 0) {
        cout << "No professors\n";
        return;
    }
    for (int i = 0; i < profList.size; i++)
        profList.data[i]->printInfo();
}

void showAllCourses() {
    cout << "\n     ALL COURSES     \n";
    if (courseList.size == 0) {
        cout << "No courses\n";
        return;
    }
    for (int i = 0; i < courseList.size; i++)
        courseList.data[i]->printCourse();
}

void showAllStudents() {
    cout << "\n     ALL STUDENTS     \n";
    if (studentCount == 0) {
        cout << "No students\n";
        return;
    }
    for (int i = 0; i < studentCount; i++)
        students[i]->printInfo();
}

void cleanAll() {
    for (int i = 0; i < studentCount; i++) delete students[i];
    studentCount = 0;

    for (int i = 0; i < courseList.size; i++) delete courseList.data[i];
    delete[] courseList.data;
    courseList.data = nullptr;
    courseList.size = 0;

    for (int i = 0; i < profList.size; i++) delete profList.data[i];
    delete[] profList.data;
    profList.data = nullptr;
    profList.size = 0;
}

int main() {
    int choice;

    do {
        cout << "\n1. Add professor\n";
        cout << "2. Add course\n";
        cout << "3. Add student\n";
        cout << "4. Enroll student to course\n";
        cout << "5. Unenroll student from course\n";
        cout << "6. Change course schedule\n";
        cout << "7. Show all professors\n";
        cout << "8. Show all courses\n";
        cout << "9. Show all students\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addProfessor(); break;
        case 2: addCourse(); break;
        case 3: addStudent(); break;
        case 4: enrollStudent(); break;
        case 5: unenrollStudent(); break;
        case 6: changeCourseSchedule(); break;
        case 7: showAllProfessors(); break;
        case 8: showAllCourses(); break;
        case 9: showAllStudents(); break;
        case 0: break;
        default: cout << "Invalid choice\n";
        }
    } while (choice != 0);

    cleanAll();
    return 0;
}