#pragma once
#include "LanguageSchoolException.h"

class InvalidOperationException : public LanguageSchoolException {
public:
    explicit InvalidOperationException(const std::string& msg) : LanguageSchoolException("Invalid operator used for object: " + msg) {}
};
