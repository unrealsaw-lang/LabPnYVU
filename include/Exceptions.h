#pragma once
#include <exception>
#include <string>

class myException : public std::exception {
	std::string message;
public:
	myException(const std::string& msg) : message(msg){}
	const char* what() const noexcept override { return message.c_str(); }
};

class invalidDataError : public myException {
public:
	invalidDataError(const std::string& msg) :myException("Invalid data: " + msg){}
};

class limitViolationError : public myException {
public:
	limitViolationError(const std::string& msg) :myException("Data above the limits: " + msg) {}

};

class missingObjectError : public myException {
public:
	missingObjectError(const std::string& msg) :myException("Object not found: " + msg) {}

};

class uniqueIdDuplicationError : public myException {
public:
	uniqueIdDuplicationError(const std::string& msg) :myException("Unique identificator duplicated: " + msg) {}

};

class invalidOperationError : public myException {
public:
	invalidOperationError(const std::string& msg) :myException("Invalid operator used for object: " + msg) {}

};