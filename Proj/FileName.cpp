//преподов создавать раньше курсов

#include <iostream>
#include <string.h>
#pragma warning(disable:4996);
using namespace std;

class Professor;
class Student;
struct Schedule {
	char* day;
	char* time;
};

class Course {
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

		cout << language << " course created!\n";
	}

	~Course() {
		delete[] language;
		delete[] level;
		delete[] schedule.day;
		delete[] schedule.time;
	}
	const char* getCourseLevel() { return level; }
	const char* getCourseLanguage() { return language; }
	const char* getCourseDay() { return schedule.day; }
	const char* getCourseTime() { return schedule.time; }
	int getCourseCurrCount() { return currcount; }
	void printCourse(Course* C) {
		cout << C->getCourseLanguage() << " course\n";
		cout << "Course level : " << C->getCourseLevel() << endl;
		cout << "Professor of the course is "; 
		cout << "Number of students: " << getCourseCurrCount() << endl;
		cout << "Course schedule - " << getCourseDay() << " " << getCourseTime() << endl;
	}
};

class Professor {
	Course* courses[10];
	int coursecount;
	int profcount;
	char* name;

public:
	Professor(const char* N) {
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

	const char* getname() { return name; }
	int getcoursecount() { return coursecount; }
	void printInfo(Professor *P) {
		cout << "Professor name is " << P->getname() << endl;
		cout << "Number of courses: " << P->getcoursecount() << endl;
	}
	void printCourse() {
		cout << "Professor " << name << " teaches:\n";
		if (coursecount == 0) cout << "no courses!\n";
		else {
			for (int i = 0; i < coursecount; i++) {
				cout << " - " << courses[i]->getCourseLanguage() << endl;
				cout << " - " << courses[i]->getCourseLevel() << endl;
				cout << " - " << courses[i]->getCourseDay() << endl;
				cout << " - " << courses[i]->getCourseTime() << endl;
			}
		}
	}
};

class Student {
	Course* courses[10];
	int coursecount;
	char* name;

public:
	Student(const char* N) {
		name = new char[strlen(N) + 1];
		strcpy(name, N);
	};

	~Student() {
		delete[] name;
	};

	const char* getname() { return name; }
	int getcoursecount() { return coursecount; }
	void printInfo(Student* S) {
		cout << "Student name is " << S->getname() << endl;
		cout << "Number of courses: " << S->getcoursecount() << endl;
	}

};

struct ProfessorsData {
	Professor** data;
	int size;
};

void ShowProfInfo(ProfessorsData List) {
	cout << "\nList of the professors\n";
	for (int i = 0; i < List.size; i++) {
		cout << "Professor #" << i + 1 << " : "; 
		List.data[i]->printInfo(List.data[i]);
		cout << endl;
	}
}
ProfessorsData CreateProfInfo() {
	ProfessorsData List;
	int profcount = 0;
	cout << "How many professors will lead them? "; cin >> profcount;
	cin.ignore();
	List.data = new Professor * [profcount];
	List.size = 0;

	for (int i = 0; i < profcount; i++) {
		char name[100];
		cout << "Name: ";
		cin.getline(name, 100);
		int exists = 0;

		for (int j = 0; j < List.size; j++) {
			if (strcmp(List.data[j]->getname(), name) == 0) {
				exists = 1;
				break;
			}
		}
		if (exists) {
			cout << "Professor allready exists!\n";
			i--;
		}
		else List.data[List.size++] = new Professor(name);
	}

	return List;
}
void CreateCourses(ProfessorsData List) {
	int courseCount;
	cout << "How many courses do u wanna create? ";
	cin >> courseCount; cin.ignore();

	for (int i = 0; i < courseCount; i++) {
		char lang[50], lvl[20], day[4], time[6], profName[100];
		int max;
		cout << "\nCourse #" << i + 1 << endl;
		cout << "Language: "; cin >> lang;
		cout << "Level: "; cin >> lvl;
		cout << "Professors name: "; cin >> profName;
		cout << "Max students: "; cin >> max;
		cout << "Day: "; cin >> day;
		cout << "Time: "; cin >> time;

		Professor* prof = nullptr;
		for (int j = 0; j < List.size; j++) {
			if (strcmp(List.data[j]->getname(), profName) == 0) {
				prof = List.data[j];
				break;
			}
		}

		if (prof == nullptr) {
			cout << "Professor not found!\n";
			continue;
		}
		Course* C = new Course(lang, lvl, prof, day, time, max);

		if (!prof->AddCourse(C)) {
			cout << "Professor has too many courses, cant add more\n";
			delete C;
		}
	}
}
void ShowCourses(ProfessorsData List) {
	cout << "\nList of all courses:\n";
	for (int i = 0; i < List.size; i++) List.data[i]->printCourse();
}
void CleanProfData(ProfessorsData List) {
	for (int i = 0; i < List.size; i++) {
		delete List.data[i];
	}
	delete List.data;
}
int main() {
	char lvl[3], lang[50], name[100], day[4], time[6];
	ProfessorsData List = CreateProfInfo();
	ShowProfInfo(List);
	CreateCourses(List);
	ShowCourses(List);
	return 0;
}