#pragma once
#include <string>
#include "Course.h"


class Student {
	vector<Course*> courses;
	int courseCount;
	string name;

public:
	Student(string N);

	string getName() const;
	int getCourseCount() const;
	void printInfo(Student* S) const;

	void setName(string N);

	int addCourse(Course* C);

};