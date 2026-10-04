#pragma once
#include <string>
#include <vector>

class Course;
class Professor;
class Student;
class Admin;

std::string promptName(const std::string& prompt);
int promptInt(const std::string& prompt);

void operatorsMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void inheritanceMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void printMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void createMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void deleteMenu(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);

void inputById(std::vector<Course*>& allCourses, std::vector<Student*>& allStudents, std::vector<Professor*>& allProfs, std::vector<Admin*>& allAdmins);