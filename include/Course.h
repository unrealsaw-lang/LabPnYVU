#pragma once
#include <string>
#include <vector>

class Professor;
class Student;

class Course {
private:
    std::vector<Student*> studs;
    int maxCount;
    std::vector<Professor*> profs;
    std::string level;
    std::string language;
    std::string schedule;

public:

    friend std::ostream& operator<<(std::ostream& stream, const Course& course);
    friend std::istream& operator>>(std::istream& stream, Course& course);

    bool operator==(const Course& otherCourse) const; //по уровню и языку
    bool operator!=(const Course& otherCourse) const;
    bool operator<(const Course& otherCourse) const;
    bool operator>(const Course& otherCourse) const; //по числу студентов
    bool operator<=(const Course& otherCourse) const;
    bool operator>=(const Course& otherCourse) const;
    Course& operator+=(Student* s); //добавить студента
    Course& operator-=(Student* s); //убрать студента

    Course(const std::string& lang, const std::string& lvl, Professor* P, const std::string& sched, int max);
    ~Course() = default;

    std::string getCourseLevel() const;
    std::string getCourseLanguage() const;
    std::string getCourseSchedule() const;
    int getCourseCurrCount() const;
    int getCourseMaxCount() const;

    void setCourseSchedule(const std::string& schd);
    void setCourseLanguage(const std::string& lang);
    void setCourseLevel(const std::string& lvl);
    void setCourseCount(int count);

    void printCourse() const;

    Student* findStudentByName(const std::string& name) const;
    Professor* findProfessorByName(const std::string& name) const;

    int addStudent(Student* S);
    int addProfessor(Professor* P);

    void removeStudent(const Student* S);
    void removeProfessor(const Professor* P);
};
