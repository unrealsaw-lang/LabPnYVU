#include "Course.h"
#include "Professor.h"
#include <iostream>
#include <string>

using namespace std;


	Professor::Professor(string N): name(N){}

	int Professor::addCourse(Course* C) {
		if (courses.size() >= 10) {
			cout << "Professor can't have more than 10 courses.\n";
			return 0;
		}
		courses.push_back(C);
		return 1;
	}

	string Professor::getName() const { return name; }
	int Professor::getCourseCount() const { return (int)courses.size(); }

	void Professor::setName(string N) { name = N; }

	void Professor::printInfo() const {
		cout << "Professor name is " << name << endl;
		cout << "Number of courses: " << getCourseCount() << endl;
	}
	void Professor::printCourse() const {
		cout << "Professor " << name << " teaches:\n";
		if (courses.empty()) cout << "no courses!\n";
		else {
			for (int i = 0; i < courses.size(); ++i) {
				cout << " - " << courses[i]->getCourseLanguage()
					<< " (" << courses[i]->getCourseLevel() << ")\n";
			}
		}
	}
