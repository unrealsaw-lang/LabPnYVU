#pragma once
#include "LanguageSchoolException.h"

class InvalidDataException : public LanguageSchoolException {
public:
    explicit InvalidDataException(const std::string& msg) : LanguageSchoolException("Invalid data: " + msg) {}
};