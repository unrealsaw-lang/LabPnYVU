#pragma once
#include <stdexcept>
#include <string>

class LanguageSchoolException : public std::runtime_error {
public:
    explicit LanguageSchoolException(const std::string& msg): std::runtime_error("[Language school system error] " + msg) {}
};