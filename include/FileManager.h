#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include "Collection.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Admin.h"
#include "FileException.h"

class FileManager {
public:
    static void saveState(const collection<Course*>& allCourses, const collection<Student*>& allStuds, const collection<Professor*>& allProfs, const collection<Admin*>& allAdmins);
    static void loadState(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins);
    static void writeLog(const std::string& message);
    static void generateReport(const collection<Course*>& allCourses, const collection<Student*>& allStuds, const collection<Professor*>& allProfs, const collection<Admin*>& allAdmins);
};