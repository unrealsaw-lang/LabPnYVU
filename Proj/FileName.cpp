#include <iostream>
#include <string.h>
using namespace std;

struct Schedule {
	char* day;
	char* time;
};

class Course {
private:
	Student* studs[30];
	int maxcount;
	int currcount;
	Professor* prof;
	char* level;
	char* language;
	Schedule schedule;

public:

	Course(const char* lang, const char* lvl, Professor* P, const char* day, const char* time, int max) {
		language = new char[strlen(lang) + 1];
		strcpy(language, lang);

		level = new char[strlen(lvl) + 1];
		strcpy(level, lvl);

		maxcount = max;

		prof = P;

		schedule.day = new char[strlen(day) + 1];
		strcpy(schedule.day, day);

		schedule.time = new char[strlen(time) + 1];
		strcpy(schedule.time, time);

		cout << "Course " << language << " created!\n";
	}

	~Course() {
		delete[] language;
		delete[] level;
		delete[] schedule.day;
		delete[] schedule.time;
	}
};

class Professor {
	Course* courses[10];
	int coursecount;
	char* name;

public:
	Professor(char* N) {
		name = new char[strlen(N) + 1];
		strcpy(name, N);
	};

	int AddCourse(Course* C) {
		if (coursecount < 10) {
			courses[coursecount++] = C;
			return 1;
		}
		else return 0;
	}

	~Professor(){
		delete[] name;
	};
};

class Student {
private:
	Course* courses[10];
	int coursecount;
	char* name;

public:
	Student(char* N) {
		name = new char[strlen(N) + 1];
		strcpy(name, N);
	};

	int AddCourse(Course* C) {
		if (coursecount < 10) {
			courses[coursecount++] = C;
			return 1;
		}
		else return 0;
	}

	~Student() {
		delete[] name;
	};

};

int main() {
	cout << "Hello!";
	return 0;
}