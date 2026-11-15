#pragma once
#include "LanguageSchoolException.h"

class UniqueIdDuplicationException : public LanguageSchoolException {
public:
    explicit UniqueIdDuplicationException(const std::string& msg) : LanguageSchoolException("Unique identificator duplicated: " + msg) {}
};
