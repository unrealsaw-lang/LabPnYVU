#pragma once
#include <stdexcept>
#include <string>

class invalidDataError : public std::runtime_error {
public:
    explicit invalidDataError(const std::string& msg) : std::runtime_error("Invalid data: " + msg) {}
};

class limitViolationError : public std::runtime_error {
public:
    explicit limitViolationError(const std::string& msg) : std::runtime_error("Data above the limits: " + msg) {}
};

class missingObjectError : public std::runtime_error {
public:
    explicit missingObjectError(const std::string& msg) : std::runtime_error("Object not found: " + msg) {}
};

class uniqueIdDuplicationError : public std::runtime_error {
public:
    explicit uniqueIdDuplicationError(const std::string& msg) : std::runtime_error("Unique identificator duplicated: " + msg) {}
};

class invalidOperationError : public std::runtime_error {
public:
    explicit invalidOperationError(const std::string& msg) : std::runtime_error("Invalid operator used for object: " + msg) {}
};