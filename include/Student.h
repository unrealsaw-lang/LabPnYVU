#pragma once
#include <string>
#include <vector>
#include <iostream>

class Course;

class Student {
private:
    std::vector<Course*> courses;
    std::string name;

public:
    friend std::ostream& operator<<(std::ostream& stream, const Student& S);
    friend std::istream& operator>>(std::istream& stream, Student& S);

    friend bool operator==(const Student& a, const Student& b) { return a.name == b.name; }
    friend bool operator!=(const Student& a, const Student& b) { return !(a == b); }
    friend bool operator<(const Student& a, const Student& b) { return a.courses.size() < b.courses.size(); }
    friend bool operator>(const Student& a, const Student& b) { return b < a; }
    friend bool operator<=(const Student& a, const Student& b) { return !(b < a); }
    friend bool operator>=(const Student& a, const Student& b) { return !(a < b); }

    Student(const std::string& N);
    ~Student() = default;

    Student& operator+=(Course* c);
    Student& operator-=(Course* c);

    std::string getName() const { return name; }
    int getCourseCount() const { return static_cast<int>(courses.size()); }

    void setName(const std::string& N) { name = N; }

    int addCourse(Course* C);
    void removeCourse(const Course* C);
    void printInfo() const;
};