#pragma once
#include <string>
#include <vector>

class Course;

class Student {
private:
    std::vector<Course*> courses;
    std::string name;

public:
    explicit Student(const std::string& N);
    ~Student() = default;

    std::string getName() const;
    int getCourseCount() const;

    void setName(const std::string& N);

    int addCourse(Course* C);
    void removeCourse(const Course* C);

    void printInfo() const;
};