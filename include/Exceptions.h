#pragma once
#include <exception>
#include <string>

class myException : public std::exception {
	std::string message;
public:
	explicit myException(const std::string& msg) : message(msg){}
	const char* what() const noexcept override { return message.c_str(); }
};

class invalidDataError : public myException {
public:
	explicit invalidDataError(const std::string& msg) :myException("Invalid data: " + msg){}
};

class limitViolationError : public myException {
public:
	explicit limitViolationError(const std::string& msg) :myException("Data above the limits: " + msg) {}

};

class missingObjectError : public myException {
public:
	explicit missingObjectError(const std::string& msg) :myException("Object not found: " + msg) {}

};

class uniqueIdDuplicationError : public myException {
public:
	explicit uniqueIdDuplicationError(const std::string& msg) :myException("Unique identificator duplicated: " + msg) {}

};

class invalidOperationError : public myException {
public:
	explicit invalidOperationError(const std::string& msg) :myException("Invalid operator used for object: " + msg) {}

};