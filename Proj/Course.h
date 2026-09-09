#pragma once
#include <string>
#include <vector>
using namespace std;

class Professor;
class Student;

class Course {
	vector<Student*> studs;
	int maxCount;
	int currCount;
	vector<Professor*> profs;
	string level;
	string language;
	string schedule;

public:

	Course(string lang, string lvl, Professor* P, string sched, int max);

	string getCourseLevel() const;
	string getCourseLanguage()const;
	string getCourseSchedule()const;
	int getCourseCurrCount()const;
	void printCourse(Course* C)const;


	void setCourseSchedule(string schd);
	void setCourseLanguage(string lang);
	void setCourseLevel(string lvl);
	void setCourseCount(int count);

	int addStudent(Student* S);
	void addProfessor(Professor* P); 
	Student* findStudentByName(const string& name);
	Professor* findProfessorByName(const string& name);
	void removeStudent(Student* S);
	void removeProfessor(Professor* P);
};