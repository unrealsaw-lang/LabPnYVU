#pragma once
#include <string>
#include "LanguageSchoolException.h"

class FileException : public LanguageSchoolException {
public:
    explicit FileException(const std::string& msg)
        : LanguageSchoolException("[File Error] " + msg) {
    }
};