#include "Student.h"
#include "Course.h"
#include <iostream>
using namespace std;

Student::Student(string N) : name(N), courseCount(0){}

	string Student::getName() const { return name; }
	int Student::getCourseCount() const { return courseCount; }
	void Student::printInfo(Student* S) const {
		cout << "Student name is " << S->getName() << endl;
		cout << "Number of courses: " << S->getCourseCount() << endl;
	}

	void Student::setName(string N) { name = N; }

	int Student::addCourse(Course* C) {
		courses.push_back(C);
		if (!C->addStudent(this)) {
			courses.pop_back();
			return 0;
		}
		courseCount++;
		return 1;
	}
