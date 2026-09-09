#include "Professor.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Course::Course(string lang, string lvl, Professor* P, string sched, int max) :
	language(lang), level(lvl), maxCount(max), schedule(sched), currCount(0) {
	profs.push_back(P);
}
	//геттеры
	string Course::getCourseLevel() const { return level; }
	string Course::getCourseLanguage() const { return language; }
	string Course::getCourseSchedule() const { return schedule; }
	int Course::getCourseCurrCount() const { return currCount; }
	void Course::printCourse(Course *C) const {
		cout << "--------------------------------------\n";
		cout << C->getCourseLanguage() << " course\n";
		cout << "Course level : " << C->getCourseLevel() << endl;
		cout << "Professor(s) of the course is ";
		if (profs.empty()) {
			cout << "Empty";
		}
		else {
			for (size_t i = 0; i < profs.size(); ++i) {
				cout << profs[i]->getName();
				if (i != profs.size() - 1) cout << ", ";
			}
		}
		cout << '\n';
		cout << "Number of students: " << getCourseCurrCount() << endl;
		cout << "Course schedule - " << getCourseSchedule() << endl;
	}
	//сеттеры
	void Course::setCourseSchedule(string schd) {schedule = schd;}
	void Course::setCourseLanguage(string lang) {language = lang;}
	void Course::setCourseLevel(string lvl) {level = lvl;}
	void Course::setCourseCount(int count) {currCount = count;}
	//методы
	int Course::addStudent(Student* S) {
		if (currCount >= maxCount) {
			cout << "\nFailed to add!";
			return 0;
		}
		else {
			studs.push_back(S);
			currCount++;
			cout << "\nAdded successfully!";
			return 1;
		}
	};
	void Course::addProfessor(Professor* P) {
		profs.push_back(P);
	};
	Student* Course::findStudentByName(const string& name) {
		for (int i = 0; i < studs.size(); ++i) {
			if (studs[i]->getName() == name)
				return studs[i];
		}
		return nullptr;
	}
	void Course::removeStudent(Student *S) {
		for (int i = 0; i < studs.size(); ++i) {
			if (studs[i] == S) {
				studs.erase(studs.begin() + i);
				currCount--;
				break;
			}
		}
	}
	Professor* Course::findProfessorByName(const string& name) {
		for (int i = 0; i < profs.size(); ++i) {
			if (profs[i]->getName() == name)
				return profs[i];
		}
		return nullptr;
	}
	void Course::removeProfessor(Professor* P) {
		for (int i = 0; i < profs.size(); ++i) {
			if (profs[i] == P) {
				profs.erase(profs.begin() + i);
				break;
			}
		}

	}