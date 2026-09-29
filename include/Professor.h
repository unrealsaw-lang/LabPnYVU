#pragma once
#include <string>
#include <vector>
#include <iostream>

class Course;

class Professor {
    friend class Course;
private:
    int id;
    std::vector<Course*> courses;
    std::string name;

public:
    Professor(int id, const std::string& N);
    ~Professor() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    int getCourseCount() const { return (int)courses.size(); }

    void setName(const std::string& N) { name = N; }

    friend std::ostream& operator<<(std::ostream& stream, const Professor& P);
    friend std::istream& operator>>(std::istream& stream, Professor& P);

    friend bool operator==(const Professor& a, const Professor& b) { return a.id == b.id; }
    friend bool operator!=(const Professor& a, const Professor& b) { return !(a == b); }
    friend bool operator<(const Professor& a, const Professor& b) { return a.getCourseCount() < b.getCourseCount(); }
    friend bool operator>(const Professor& a, const Professor& b) { return b < a; }
    friend bool operator<=(const Professor& a, const Professor& b) { return !(b < a); }
    friend bool operator>=(const Professor& a, const Professor& b) { return !(a < b); }

    Professor& operator+=(Course* c);
    Professor& operator-=(Course* c);

    void printInfo() const;
};