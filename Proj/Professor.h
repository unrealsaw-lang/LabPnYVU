#pragma once
#include <string>
#include "Course.h"
using namespace std;

class Professor {
	vector<Course*> courses;
	string name;

public:
	Professor(string N);

	int addCourse(Course* C);

	string getName() const;
	int getCourseCount() const;

	void setName(string N);

	void printInfo() const;
	void printCourse() const;
};
