#pragma once

#include <string>

class ILogger {
    public:
        virtual void write(const std::string&) = 0;
};