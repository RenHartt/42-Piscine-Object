#pragma once 

#include "ILogger.hpp"
#include <iostream>

class OStreamLogger: public ILogger {
    private:
        std::ostream& stream;
    public:
        OStreamLogger(std::ostream& stream): stream(stream) {}
        void write(const std::string& log) override {
            stream << log << std::endl;
        }
};