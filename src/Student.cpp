#include "Student.h"
#include "Course.h"
#include <iostream>
using namespace std;

Student::Student(string N) : name(N){}

	string Student::getName() const { return name; }
	int Student::getCourseCount() const { return (int)courses.size(); }
	void Student::printInfo(Student* S) const {
		cout << "\n--------------------------------------";
		cout << "\nStudent " << S->getName() << " currently taking part in next courses: ";
		int size = S->getCourseCount();
		for (int i = 0; i < size; i++) {
			cout << " " << courses[i]->getCourseLanguage();
		}
		cout << "\nTotal number of this student courses: " << S->getCourseCount();
		
	}

	void Student::setName(string N) { name = N; }

	int Student::addCourse(Course* C) {
		if (!C->addStudent(this)) return 0;

		courses.push_back(C);
		return 1;
	}
