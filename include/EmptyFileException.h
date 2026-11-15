#pragma once
#include "FileException.h"
class EmptyFileException : public FileException {
public:
    explicit EmptyFileException(const std::string& msg) : FileException(msg) {}
};