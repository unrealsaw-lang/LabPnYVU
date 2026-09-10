#pragma once
#include <string>
#include <vector>

class Professor;
class Student;

class Course {
private:
    std::vector<Student*> studs;
    int maxCount;
    int currCount;
    std::vector<Professor*> profs;
    std::string level;
    std::string language;
    std::string schedule;

public:
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

    int addStudent(Student* S);
    int addProfessor(Professor* P);
    Student* findStudentByName(const std::string& name) const;
    Professor* findProfessorByName(const std::string& name) const;
    void removeStudent(const Student* S);
    void removeProfessor(const Professor* P);
};