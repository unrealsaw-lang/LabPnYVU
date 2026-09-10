#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Professor.h"
#include "Student.h"

using namespace std;
Course* findCourseByTitle(vector<Course*>& allC) {
	cout << "Enter course title: ";
	string courseTitle; getline(cin, courseTitle);

	cout << "Enter course level: ";
	string courseLevel; getline(cin, courseLevel);

	for (int i = 0; i < allC.size(); ++i) {
		if (allC[i]->getCourseLanguage() == courseTitle && allC[i]->getCourseLevel() == courseLevel)
			return allC[i];
	}
	return nullptr;
}
void createCourse(vector<Professor*>& allProfs, vector<Course*>& allC) {
	string language, level, profName, schedule;
	int max;
	cout << "Enter course language: ";
	cin.ignore();
	getline(cin, language);
	cout << "Enter course level: ";
	getline(cin, level);
	cout << "Enter course professor name: ";
	getline(cin, profName);
	cout << "Enter course schedule: ";
	getline(cin, schedule);
	cout << "Enter course max capacity: "; cin >> max;

	Professor* prof = nullptr;
	for (int i = 0; i < allProfs.size(); ++i) {
		Professor* p = allProfs[i];
		if (p->getName() == profName) {
			prof = p;
			break;
		}
	}
	if (!prof) {
		cout << "\nProfessor not found...\n";
		return;
	}

	Course* C = new Course(language, level, prof, schedule, max);
	allC.push_back(C);
	cout << "\nCourse created!\n";
}
void deleteCourse(vector<Professor*>& allProfs, vector<Course*>& allC) {
	Course *delC = findCourseByTitle(allC);
	for (int i = 0; i < allC.size(); ++i) {
		if (allC[i] == delC) {
			allC.erase(allC.begin() + i);
			break;
		}
	}
}
void enrollStudentToCourse(vector<Course*>& allC) {
	cout << "Enter student name: "; cin.ignore();
	string name; getline(cin, name);

	Course* C = findCourseByTitle(allC);
	if (C == nullptr) {
		cout << "\nCourse not found...\n";
		return;
	}

	Student* newStudent = new Student(name);
	if (newStudent->addCourse(C)) {
		cout << "\nSuccess!\n";
	}
	else {
		delete newStudent;
		cout << "\nFailed...\n";
	}
}
void addProfessorToCourse(vector<Course*>& allC) {
	cout << "\nEnter professor name: ";
	string name; getline(cin, name);
	Professor* newProfessor = new Professor(name);

	Course* C = findCourseByTitle(allC);
	C->addProfessor(newProfessor);
	newProfessor->addCourse(C);
}
void kickStudent(vector<Course*>& allC) {
	Course* C = findCourseByTitle(allC);

	cout << "Enter students name: "; cin.ignore();
	string name; getline(cin, name);
	
	Student* s = C->findStudentByName(name);
	if (s != nullptr) {
		C->removeStudent(s);
		cout << "\nStudent removed!\n";
	}
	else {
		cout << "\nStudent not found...\n";
	}
}
void removeProfessor(vector<Course*>& allC) {
	Course* C = findCourseByTitle(allC);

	cout << "Enter professor name: "; cin.ignore();
	string name; getline(cin, name);

	Professor* p = C->findProfessorByName(name);
	if (p != nullptr) {
		C->removeProfessor(p);
		cout << "\Professor removed!\n";
	}
	else {
		cout << "\nProfessor not found...\n";
	}
}
void initData(vector<Professor*>& allProfs, vector<Course*>& allC) {
	Professor* P1 = new Professor("Smith");
	Professor* P2 = new Professor("Brown");
	Professor* P3 = new Professor("Johnson");
	Professor* P4 = new Professor("Potapenko");

	allProfs.push_back(P1);
	allProfs.push_back(P2);	
	allProfs.push_back(P3);
	allProfs.push_back(P4);

	Course* C1 = new Course("English", "A1", P1, "Mon 10:00", 30);
	Course* C2 = new Course("Deutsche", "A2", P1, "Tue 12:00", 20);
	Course* C3 = new Course("Russian", "B1", P2, "Wed 10:00", 10);
	Course* C4 = new Course("Deutsche", "C1", P3, "Thu 14:00", 30);
	Course* C5 = new Course("English", "B2", P4, "Fri 16:00", 25);

	allC.push_back(C1);
	allC.push_back(C2);
	allC.push_back(C3);
	allC.push_back(C4);
	allC.push_back(C5);
}
void showTestData(vector<Professor*>& allProfs, vector<Course*>& allC) {
	int size = allC.size();
	for (int i = 0; i < size; i++)
	allC[i]->printCourse(allC[i]);
}
void printStudentInfo(vector<Course*>& allC) {
	cout << "Enter student name: "; cin.ignore();
	string name; getline(cin, name);

	int size = allC.size();
	for (int i = 0; i < size; i++) {
		Student* S = allC[i]->findStudentByName(name);
		if (S != nullptr) {
			S->printInfo(S);
			return;
		}
	}
	cout << "\nStudent not found...\n";
}
void printProfessorInfo(vector<Course*>& allC) {
	cout << "Enter professor name: "; cin.ignore();
	string name; getline(cin, name);

	int size = allC.size();
	for (int i = 0; i < size; i++) {
		Professor* P = allC[i]->findProfessorByName(name);
		if (P != nullptr) {
			P->printInfo(P);
			return;
		}
	}
	cout << "\nProfessor not found...\n";
}
int main() {
	vector<Professor*> allProfessors;
	vector<Course*> allCourses;
	initData(allProfessors, allCourses);

	int choice;

	do {
		cout << "\n1. Print all data";
		cout << "\n2. Print student info";
		cout << "\n3. Print professor info";
		cout << "\n4. Add course";
		cout << "\n5. Add student";
		cout << "\n6. Add professor";
		cout << "\n7. Remove student";
		cout << "\n8. Remove professor";
		cout << "\n9. Delete course";
		cout << "\n0. Exit";
		cout << "\nYour choice: "; cin >> choice;

		switch (choice) {
		case 1: showTestData(allProfessors, allCourses); break;
		case 2: printStudentInfo(allCourses);  break;
		case 3: printProfessorInfo(allCourses);  break;
		case 4: createCourse(allProfessors, allCourses); break;
		case 5:enrollStudentToCourse(allCourses); break;
		case 6: addProfessorToCourse(allCourses); break;
		case 7: kickStudent(allCourses); break;
		case 8: removeProfessor(allCourses); break;
		case 9: deleteCourse(allProfessors, allCourses); break;
		}
	} while (choice != 0);
	return 0;
}