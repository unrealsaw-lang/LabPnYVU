#pragma once
#include <string>
#include <vector>
#include <iostream>

class Course;

class Professor {
private:
    std::vector<Course*> courses;
    std::string name;

public:
    friend std::ostream& operator<<(std::ostream& stream, const Professor& P);
    friend std::istream& operator>>(std::istream& stream, Professor& P);

    friend bool operator==(const Professor& a, const Professor& b) { return a.name == b.name; }
    friend bool operator!=(const Professor& a, const Professor& b) { return !(a == b); }
    friend bool operator<(const Professor& a, const Professor& b) { return a.courses.size() < b.courses.size(); }
    friend bool operator>(const Professor& a, const Professor& b) { return b < a; }
    friend bool operator<=(const Professor& a, const Professor& b) { return !(b < a); }
    friend bool operator>=(const Professor& a, const Professor& b) { return !(a < b); }

    Professor(const std::string& N);
    ~Professor() = default;

    Professor& operator+=(Course* c);
    Professor& operator-=(Course* c);

    std::string getName() const { return name; }
    int getCourseCount() const { return static_cast<int>(courses.size()); }

    void setName(const std::string& N) { name = N; }

    int addCourse(Course* C);
    void removeCourse(const Course* C);
    void printInfo() const;
};