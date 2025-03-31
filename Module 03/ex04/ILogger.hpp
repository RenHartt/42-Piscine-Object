#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "IHeader.hpp"

class ILogger {
protected:
    IHeader* header;
public:
    ILogger(IHeader* header = nullptr): header(header) {}
    ILogger(const ILogger&) = delete;
    ILogger& operator=(const ILogger&) = delete;
    ILogger(ILogger&&) = delete;
    ILogger& operator=(ILogger&&) = delete;
    virtual ~ILogger() {
        if (header != nullptr) {
            delete header;
        }
    }
    virtual void write(const std::string&) = 0;
};

class FileLogger: public ILogger {
private:
    std::fstream stream;
public:
    FileLogger(const std::string& filename, IHeader* header = nullptr) {
        stream.open(filename, std::ios::out | std::ios::app);
        this->header = header;
    }
    ~FileLogger() {
        if (stream.is_open()) {
            stream.close();
        }
    }
    
    void write(const std::string& log) override {
        if (header != nullptr) {
            stream << header->getHeader() << ": ";
        }
        stream << log << std::endl;
    }
};

class OStreamLogger: public ILogger {
private:
    std::ostream& stream;
public:
    OStreamLogger(std::ostream& stream, IHeader* header = nullptr): stream(stream) {
        this->header = header;
    }
    void write(const std::string& log) override {
        if (header != nullptr) {
            stream << header->getHeader() << ": ";
        }
        stream << log << std::endl;
    }
};