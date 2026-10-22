#pragma once
#include <string>
#include "Collection.h"

class Course;
class Professor;
class Student;
class Admin;

std::string promptName(const std::string& prompt);
int promptInt(const std::string& prompt);

void templatesMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void printMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);
void enrollMenu(collection<Course*>&, collection<Student*>&, collection<Professor*>&, collection<Admin*>&);