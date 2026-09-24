#pragma once
#include <string>
#include <vector>
#include <iostream>

class Professor;
class Student;

class Course {
private:
    std::vector<Student*> studs;
    std::vector<Professor*> profs;
    int maxCount;
    std::string level;
    std::string language;
    std::string schedule;

public:
    friend std::ostream& operator<<(std::ostream& stream, const Course& course);
    friend std::istream& operator>>(std::istream& stream, Course& course);

    friend bool operator==(const Course& a, const Course& b) { return a.language == b.language && a.level == b.level; }
    friend bool operator!=(const Course& a, const Course& b) { return !(a == b); }
    friend bool operator<(const Course& a, const Course& b) { return a.studs.size() < b.studs.size(); }
    friend bool operator>(const Course& a, const Course& b) { return b < a; }
    friend bool operator<=(const Course& a, const Course& b) { return !(b < a); }
    friend bool operator>=(const Course& a, const Course& b) { return !(a < b); }

    Course(const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max);
    ~Course() = default;

    Course& operator+=(Student* s);
    Course& operator-=(Student* s);
    Course& operator+=(Professor* p);
    Course& operator-=(Professor* p);

    std::string getCourseLevel() const { return level; }
    std::string getCourseLanguage() const { return language; }
    std::string getCourseSchedule() const { return schedule; }
    int getCourseCurrCount() const { return static_cast<int>(studs.size()); }
    int getCourseMaxCount() const { return maxCount; }

    void setCourseSchedule(const std::string& schd) { schedule = schd; }
    void setCourseLanguage(const std::string& lang) { language = lang; }
    void setCourseLevel(const std::string& lvl) { level = lvl; }

    void printCourse() const;

    Student* findStudentByName(const std::string& name) const;
    Professor* findProfessorByName(const std::string& name) const;

    int addStudent(Student* S);
    int addProfessor(Professor* P);

    void removeStudent(const Student* S);
    void removeProfessor(const Professor* P);
};