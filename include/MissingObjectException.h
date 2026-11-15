#pragma once
#include "LanguageSchoolException.h"

class MissingObjectException : public LanguageSchoolException {
public:
    explicit MissingObjectException(const std::string& msg) : LanguageSchoolException("Object not found: " + msg) {}
};
