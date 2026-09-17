#pragma once
#include <string>
#include <vector>

class Course;

class Student {

private:
    std::vector<Course*> courses;
    std::string name;

public:
    friend std::ostream& operator<<(std::ostream& stream, const Student& S);
    bool operator==(const Student& otherStudent);
    bool operator>(const Student& otherStudent);
    bool operator<(const Student& otherStudent);

    Student(const std::string& N);
    ~Student() = default;

    std::string getName() const;
    int getCourseCount() const;

    void setName(const std::string& N);

    int addCourse(Course* C);
    void removeCourse(const Course* C);

    void printInfo() const;
};

