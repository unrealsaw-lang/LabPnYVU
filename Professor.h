#pragma once
#include <string>
#include "Course.h"
using namespace std;

class Professor {
	vector<Course*> courses;
	int courseCount;
	int profCount;
	string name;

public:
	Professor(string N);

	int addCourse(Course* C);

	string getName() const;
	int getCourseCount() const;

	void setName(string N);

	void printInfo(Professor* P) const;
	void printCourse() const;
};
