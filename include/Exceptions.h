#pragma once
#include <stdexcept>
#include <string>

class myException : public std::runtime_error {
public:
    explicit myException(const std::string& msg)
        : std::runtime_error("[Language school system error] " + msg) {}
};

class invalidDataError : public myException {
public:
    explicit invalidDataError(const std::string& msg) : myException("Invalid data: " + msg) {}
};

class courseLimitViolationError : public myException {
public:
    explicit courseLimitViolationError(const std::string& msg) : myException("Data above the limits: " + msg) {}
};

class missingObjectError : public myException {
public:
    explicit missingObjectError(const std::string& msg) : myException("Object not found: " + msg) {}
};

class uniqueIdDuplicationError : public myException {
public:
    explicit uniqueIdDuplicationError(const std::string& msg) : myException("Unique identificator duplicated: " + msg) {}
};

class invalidOperationError : public myException {
public:
    explicit invalidOperationError(const std::string& msg) : myException("Invalid operator used for object: " + msg) {}
};