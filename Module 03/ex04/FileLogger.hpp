#pragma once 

#include "ILogger.hpp"
#include <fstream>

class FileLogger: public ILogger {
    private:
        std::fstream stream;
    public:
        FileLogger(const std::string& filename) {
            stream.open(filename, std::ios::out | std::ios::app);
        }
        void write(const std::string& log) override {
            stream << log << std::endl;
        }
};