#pragma once
#include <string>
#include <vector>

class Course;
class Professor;
class Student;
class Admin;

std::string promptName(const std::string& prompt);
int promptInt(const std::string& prompt);

Course* findCourseById(const std::vector<Course*>& v, int id);
Student* findStudentById(const std::vector<Student*>& v, int id);
Professor* findProfessorById(const std::vector<Professor*>& v, int id);
Admin* findAdminById(const std::vector<Admin*>& v, int id);
Student* findStudentByName(const std::vector<Student*>& v, const std::string& name);
Professor* findProfessorByName(const std::vector<Professor*>& v, const std::string& name);
Course* findCourseByTitle(const std::vector<Course*>& v);

void inheritanceMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void printMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);
void createMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);
void deleteMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);
void enrollMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void inputById(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);