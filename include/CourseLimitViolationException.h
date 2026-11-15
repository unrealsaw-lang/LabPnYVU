#pragma once
#include "LanguageSchoolException.h"

class CourseLimitViolationException : public LanguageSchoolException {
public:
    explicit CourseLimitViolationException(const std::string& msg) : LanguageSchoolException("Data above the limits: " + msg) {}
};