#pragma once
#include <string>
#include "Collection.h"

class Course;
class Professor;
class Student;
class Admin;

std::string promptName(const std::string& prompt);
int promptInt(const std::string& prompt);

void mainMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void printMenu(const collection<Course*>&, const collection<Student*>&, const collection<Professor*>&, const collection<Admin*>&);
void enrollMenu(const collection<Course*>&, const collection<Student*>&, const collection<Professor*>&, const collection<Admin*>&);