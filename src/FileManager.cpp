#include "FileManager.h"
#include "EmptyFileException.h"
#include "InvalidFileDataException.h"

void FileManager::writeLog(const std::string& message) {
    std::ofstream logFile("data/journal.log", std::ios::app);
    if (!logFile.is_open()) throw FileException("Cannot open journal.log");

    time_t seconds = time(NULL);
    tm timeInfo;
    localtime_s(&timeInfo, &seconds);

    char timeBuffer[32];
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

    logFile << "[" << timeBuffer << "] " << message << "\n";
}

void FileManager::saveState(const collection<Course*>& allCourses,
    const collection<Student*>& allStuds,
    const collection<Professor*>& allProfs,
    const collection<Admin*>& allAdmins) {

    std::ofstream studFile("data/students.txt");
    if (!studFile.is_open()) throw FileException("Cannot open file: data/students.txt");

    for (int i = 0; i < allStuds.getSize(); i++) {
        Student* currentStud = allStuds.get(i);
        studFile << currentStud->getId() << "|" << currentStud->getName() << "|" << currentStud->getStudentId() << "|";
        const auto& studentMarks = currentStud->getMarks();
        for (size_t j = 0; j < studentMarks.size(); j++) {
            studFile << studentMarks[j];
            if (j + 1 < studentMarks.size()) {
                studFile << ",";
            }
        }
        studFile << "\n";
    }
    studFile.close();

    std::ofstream profFile("data/professors.txt");
    if (!profFile.is_open()) throw FileException("Cannot open file: data/professors.txt");

    for (int i = 0; i < allProfs.getSize(); i++) {
        Professor* currentProf = allProfs.get(i);
        profFile << currentProf->getId() << "|" << currentProf->getName() << "|" << currentProf->getDepartment() << "|";
        const auto& profFeedbacks = currentProf->getFeedbacks();
        for (size_t j = 0; j < profFeedbacks.size(); j++) {
            profFile << profFeedbacks[j];
            if (j + 1 < profFeedbacks.size()) {
                profFile << ",";
            }
        }
        profFile << "\n";
    }
    profFile.close();

    std::ofstream admFile("data/admins.txt");
    if (!admFile.is_open()) throw FileException("Cannot open file: data/admins.txt");

    for (int i = 0; i < allAdmins.getSize(); i++) {
        Admin* currentAdmin = allAdmins.get(i);
        admFile << currentAdmin->getId() << "|" << currentAdmin->getName() << "|" << currentAdmin->getResponsibility() << "\n";
    }
    admFile.close();

    std::ofstream courseFile("data/courses.txt");
    if (!courseFile.is_open()) throw FileException("Cannot open file: data/courses.txt");

    for (int i = 0; i < allCourses.getSize(); i++) {
        Course* currentCourse = allCourses.get(i);
        courseFile << currentCourse->getId() << "|" << currentCourse->getLanguage() << "|"
            << currentCourse->getLevel() << "|" << currentCourse->getSchedule() << "|"
            << currentCourse->getMaxCount() << "|professors:";

        const auto& courseProfs = currentCourse->getProfessors();
        for (int j = 0; j < courseProfs.getSize(); j++) {
            courseFile << courseProfs.get(j)->getId();
            if (j + 1 < courseProfs.getSize()) {
                courseFile << ",";
            }
        }

        courseFile << "|students:";
        const auto& courseStuds = currentCourse->getStudents();
        for (int j = 0; j < courseStuds.getSize(); j++) {
            courseFile << courseStuds.get(j)->getId();
            if (j + 1 < courseStuds.getSize()) {
                courseFile << ",";
            }
        }
        courseFile << "\n";
    }
    courseFile.close();

    writeLog("State saved");
}

void FileManager::loadState(collection<Course*>& allCourses, collection<Student*>& allStuds, collection<Professor*>& allProfs, collection<Admin*>& allAdmins) {
    std::ifstream checkFile("data/students.txt");
    if (!checkFile.is_open()) throw FileException("Empty load");
    checkFile.close();

    std::vector<Student*> tempStuds;
    std::vector<Professor*> tempProfs;
    std::vector<Admin*> tempAdmins;
    std::vector<Course*> tempCourses;

    try {
        std::string line;

        std::ifstream studFile("data/students.txt");
        while (std::getline(studFile, line)) {
            if (line.empty() || line.rfind("#", 0) == 0) continue;
            std::stringstream ss(line);
            std::string idStr, name, num, marks;
            std::getline(ss, idStr, '|');
            std::getline(ss, name, '|');
            std::getline(ss, num, '|');
            std::getline(ss, marks);

            Student* S = new Student(std::stoi(idStr), name, num);
            if (!marks.empty()) {
                std::stringstream ms(marks);
                std::string m;
                while (std::getline(ms, m, ',')) {
                    if (!m.empty()) S->addMark(std::stoi(m));
                }
            }
            tempStuds.push_back(S);
        }
        studFile.close();

        std::ifstream profFile("data/professors.txt");
        while (std::getline(profFile, line)) {
            if (line.empty() || line.rfind("#", 0) == 0) continue;
            std::stringstream ss(line);
            std::string idStr, name, dep, feedbacks;
            std::getline(ss, idStr, '|');
            std::getline(ss, name, '|');
            std::getline(ss, dep, '|');
            std::getline(ss, feedbacks);

            Professor* P = new Professor(std::stoi(idStr), name, dep);
            if (!feedbacks.empty()) {
                std::stringstream fs(feedbacks);
                std::string f;
                while (std::getline(fs, f, ',')) {
                    if (!f.empty()) P->rate(std::stoi(f));
                }
            }
            tempProfs.push_back(P);
        }
        profFile.close();

        std::ifstream admFile("data/admins.txt");
        while (std::getline(admFile, line)) {
            if (line.empty() || line.rfind("#", 0) == 0) continue;
            std::stringstream ss(line);
            std::string idStr, name, resp;
            std::getline(ss, idStr, '|');
            std::getline(ss, name, '|');
            std::getline(ss, resp);
            tempAdmins.push_back(new Admin(std::stoi(idStr), name, resp));
        }
        admFile.close();

        std::ifstream courseFile("data/courses.txt");
        while (std::getline(courseFile, line)) {
            if (line.empty() || line.rfind("#", 0) == 0) continue;
            std::stringstream ss(line);
            std::string idStr, lang, lvl, sched, maxStr, profSeg, studSeg;
            std::getline(ss, idStr, '|');
            std::getline(ss, lang, '|');
            std::getline(ss, lvl, '|');
            std::getline(ss, sched, '|');
            std::getline(ss, maxStr, '|');
            std::getline(ss, profSeg, '|');
            std::getline(ss, studSeg);

            int profId = std::stoi(profSeg.substr(11));
            Professor* mainProf = nullptr;
            for (auto P : tempProfs) {
                if (P->getId() == profId) { mainProf = P; break; }
            }
            if (!mainProf) continue;

            Course* C = new Course(std::stoi(idStr), lang, lvl, mainProf, sched, std::stoi(maxStr));

            std::string studIds = studSeg.substr(9);
            if (!studIds.empty()) {
                std::stringstream sts(studIds);
                std::string sId;
                while (std::getline(sts, sId, ',')) {
                    if (!sId.empty()) {
                        int targetId = std::stoi(sId);
                        for (auto st : tempStuds) {
                            if (st->getId() == targetId) { *C += st; break; }
                        }
                    }
                }
            }
            tempCourses.push_back(C);
        }
        courseFile.close();

        for (auto temp : allCourses) delete temp;
        for (auto temp : allProfs) delete temp;
        for (auto temp : allStuds) delete temp;
        for (auto temp : allAdmins) delete temp;

        allCourses.clear(); allStuds.clear(); allProfs.clear(); allAdmins.clear();

        for (auto temp : tempStuds) allStuds.add(temp);
        for (auto temp : tempProfs) allProfs.add(temp);
        for (auto temp : tempAdmins) allAdmins.add(temp);
        for (auto temp : tempCourses) allCourses.add(temp);

        writeLog("State loaded");
    }
    catch (...) {
        for (auto temp : tempStuds) delete temp;
        for (auto temp : tempProfs) delete temp;
        for (auto temp : tempAdmins) delete temp;
        for (auto temp : tempCourses) delete temp;
        throw FileException("Invalid format or corrupted data");
    }
}

void FileManager::generateReport(const collection<Course*>& allCourses,
    const collection<Student*>& allStuds,
    const collection<Professor*>& allProfs,
    const collection<Admin*>& allAdmins) {

    std::ofstream reportFile("data/report.txt");
    if (!reportFile.is_open()) throw FileException("Cannot create report.txt");

    reportFile << "Language school report:\n";

    reportFile << "\nCourse info:\n";
    for (int i = 0; i < allCourses.getSize(); i++) {
        Course* currentCourse = allCourses.get(i);
        reportFile << i + 1 << ") id: " << currentCourse->getId()
            << ", language: " << currentCourse->getLanguage()
            << ", level: " << currentCourse->getLevel()
            << ", capacity: " << currentCourse->getStudentCount() << "/" << currentCourse->getMaxCount()
            << ", schedule: " << currentCourse->getSchedule() << "\nprofessors: ";

        const auto& courseProfs = currentCourse->getProfessors();
        if (courseProfs.getSize() == 0) reportFile << "none";
        else {
            int profIndex = 0;
            for (auto profPtr : courseProfs) {
                reportFile << profPtr->getName();
                profIndex++;
                if (profIndex < courseProfs.getSize()) reportFile << ", ";
            }
        }

        reportFile << "\nstudents: ";
        const auto& courseStuds = currentCourse->getStudents();
        if (courseStuds.getSize() == 0) reportFile << "none";
        else {
            int studIndex = 0;
            for (auto studPtr : courseStuds) {
                reportFile << studPtr->getName();
                studIndex++;
                if (studIndex < courseStuds.getSize()) reportFile << ", ";
            }
        }
        reportFile << "\n";
    }

    reportFile << "\nStudent info:\n";
    for (int i = 0; i < allStuds.getSize(); i++) {
        Student* currentStud = allStuds.get(i);
        reportFile << i + 1 << ") id: " << currentStud->getId()
            << ", name: " << currentStud->getName()
            << ", student number: " << currentStud->getStudentId() << "\n   marks: ";

        const auto& studentMarks = currentStud->getMarks();
        if (studentMarks.empty()) reportFile << "no marks";
        else {
            for (size_t j = 0; j < studentMarks.size(); j++) {
                reportFile << studentMarks[j];
                if (j + 1 < studentMarks.size()) reportFile << ", ";
            }
        }
        reportFile << "\n";
    }

    reportFile << "\nProfessor info:\n";
    for (int i = 0; i < allProfs.getSize(); i++) {
        Professor* currentProf = allProfs.get(i);
        reportFile << i + 1 << ") id: " << currentProf->getId()
            << ", name: " << currentProf->getName()
            << ", department: " << currentProf->getDepartment() << "\n   feedbacks: ";

        const auto& profFeedbacks = currentProf->getFeedbacks();
        if (profFeedbacks.empty()) {
            reportFile << "no feedbacks";
        }
        else {
            for (size_t j = 0; j < profFeedbacks.size(); j++) {
                reportFile << profFeedbacks[j];
                if (j + 1 < profFeedbacks.size()) reportFile << ", ";
            }
        }
        reportFile << "\n";
    }

    reportFile << "\nAdmin info:\n";
    for (int i = 0; i < allAdmins.getSize(); i++) {
        Admin* currentAdmin = allAdmins.get(i);
        reportFile << i + 1 << ") id: " << currentAdmin->getId()
            << ", name: " << currentAdmin->getName()
            << ", responsibility: " << currentAdmin->getResponsibility() << "\n";
    }

    reportFile << "\n";
    reportFile.close();

    writeLog("Report created");
}