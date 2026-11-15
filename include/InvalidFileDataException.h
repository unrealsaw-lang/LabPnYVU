#pragma once
#include "FileException.h"
class InvalidFileDataException : public FileException {
public:
    explicit InvalidFileDataException(const std::string& msg) : FileException(msg) {}
};