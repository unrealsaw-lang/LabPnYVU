#pragma once
#include <string>
#include <vector>
#include <iostream>

class Course;

class Student {
    friend class Course;
private:
    int id;
    std::vector<Course*> courses;
    std::string name;

public:
    Student(int id, const std::string& N);
    ~Student() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getCourseCount() const { return (int)courses.size(); }

    void setName(const std::string& N) { name = N; }

    friend std::ostream& operator<<(std::ostream& stream, const Student& S);
    friend std::istream& operator>>(std::istream& stream, Student& S);

    friend bool operator==(const Student& a, const Student& b) { return a.id == b.id; }
    friend bool operator!=(const Student& a, const Student& b) { return !(a == b); }
    friend bool operator<(const Student& a, const Student& b) { return a.getCourseCount() < b.getCourseCount(); }
    friend bool operator>(const Student& a, const Student& b) { return b < a; }
    friend bool operator<=(const Student& a, const Student& b) { return !(b < a); }
    friend bool operator>=(const Student& a, const Student& b) { return !(a < b); }

    Student& operator+=(Course* c);
    Student& operator-=(Course* c);

    void printInfo() const;
};