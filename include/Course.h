#pragma once
#include <string>
#include <vector>
#include <iostream>

class Professor;
class Student;
class Admin;

class Course {
    friend class Student;
    friend class Professor;
    friend class Admin;
private:
    int id;
    std::vector<Student*> studs;
    std::vector<Professor*> profs;
    int maxCount;
    std::string level;
    std::string language;
    std::string schedule;

public:
    friend std::ostream& operator<<(std::ostream& stream, const Course& course);
    friend std::istream& operator>>(std::istream& stream, Course& course);

    friend bool operator==(const Course& C1, const Course& C2) { return C1.id == C2.id; }
    friend bool operator!=(const Course& C1, const Course& C2) { return !(C1 == C2); }
    friend bool operator<(const Course& C1, const Course& C2) { return C1.getCourseCurrCount() < C2.getCourseCurrCount(); }
    friend bool operator>(const Course& C1, const Course& C2) { return C2 < C1; }
    friend bool operator<=(const Course& C1, const Course& C2) { return !(C2 < C1); }
    friend bool operator>=(const Course& C1, const Course& C2) { return !(C1 < C2); }

    Course(int id, const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max);
    ~Course() = default;

    Course& operator+=(Student* S);
    Course& operator-=(Student* S);
    Course& operator+=(Professor* P);
    Course& operator-=(Professor* P);

    int getId() const { return id; }
    std::string getCourseLevel() const { return level; }
    std::string getCourseLanguage() const { return language; }
    std::string getCourseSchedule() const { return schedule; }
    int getCourseCurrCount() const { return (int)studs.size(); }
    int getCourseMaxCount() const { return maxCount; }

    void setCourseSchedule(const std::string& schd) { schedule = schd; }
    void setCourseLanguage(const std::string& lang) { language = lang; }
    void setCourseLevel(const std::string& lvl) { level = lvl; }

    void printCourse() const;
    Student* findStudentByName(const std::string& name) const;
    Professor* findProfessorByName(const std::string& name) const;
};