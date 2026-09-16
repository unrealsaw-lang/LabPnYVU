#pragma once
#include <string>
#include <vector>

class Course;

class Professor {
private:
    std::vector<Course*> courses;
    std::string name;

public:
    Professor(const std::string& N);
    ~Professor() = default;

    std::string getName() const;
    int getCourseCount() const;

    void setName(const std::string& N);

    int addCourse(Course* C);

    void removeCourse(const Course* C);

    void printInfo() const;
};
