#pragma once
#include <string>
#include "Collection.h"

class Course;
class Professor;
class Student;
class Admin;

std::string promptName(const std::string& prompt);
int promptInt(const std::string& prompt);

Course* findCourseById(const collection<Course*>& allCourses, int id);
Student* findStudentById(const collection<Student*>& allStuds, int id);
Professor* findProfessorById(const collection<Professor*>& allProfs, int id);
Admin* findAdminById(const collection<Admin*>& allAdmins, int id);
Student* findStudentByName(const collection<Student*>& allStuds, const std::string& name);
Professor* findProfessorByName(const collection<Professor*>& allProfs, const std::string& name);
Course* findCourseByTitle(const collection<Course*>& allCourses);

void templatesMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void printMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void createMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void deleteMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void enrollMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);

void printByLanguageLevel(const collection<Course*>& allCourses);