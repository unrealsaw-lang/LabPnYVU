#pragma once
#include <string>
#include <vector>

class Course;

class Professor {
private:
    std::vector<Course*> courses;
    std::string name;

public:
    explicit Professor(const std::string& N);
    ~Professor() = default;

    int addCourse(Course* C);
    void removeCourse(const Course* C);

    std::string getName() const;
    int getCourseCount() const;

    void setName(const std::string& N);

    void printInfo() const;
};