#include <iostream>
#include <string>
#include "Professor.h"
#include "Course.h"

using namespace std;


	Professor::Professor(string N): name(N){}

	int Professor::addCourse(Course* C) {
		if (courseCount < 10) {
			courses[courseCount++] = C;
			return 1;
		}
		else return 0;
	}

	string Professor::getName() const { return name; }
	int Professor::getCourseCount() const { return courseCount; }

	void Professor::setName(string N) { name = N; }

	void Professor::printInfo(Professor* P) const {
		cout << "Professor name is " << P->getName() << endl;
		cout << "Number of courses: " << P->getCourseCount() << endl;
	}
	void Professor::printCourse() const {
		cout << "Professor " << name << " teaches:\n";
		if (courseCount == 0) cout << "no courses!\n";
		else {
			for (int i = 0; i < courseCount; i++) {
				cout << " - " << courses[i]->getCourseLanguage() << endl;
				cout << " - " << courses[i]->getCourseLevel() << endl;
			}
		}
	}
