#include <iostream>
#include <string>
#include <vector>
#include "Professor.h"
#include "Student.h"

using namespace std;

Course::Course(string lang, string lvl, Professor* P, string sched, int max) :
	language(lang), level(lvl), maxCount(max), prof(P), schedule(sched), currCount(0) {
		cout << language << " course created!\n";
	}
	//геттеры
	string Course::getCourseLevel() const { return level; }
	string Course::getCourseLanguage() const { return language; }
	string Course::getCourseSchedule() const { return schedule; }
	int Course::getCourseCurrCount() const { return currCount; }
	void Course::printCourse(Course* C) const {
		cout << C->getCourseLanguage() << " course\n";
		cout << "Course level : " << C->getCourseLevel() << endl;
		cout << "Professor of the course is " << prof->getName() << endl;
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

