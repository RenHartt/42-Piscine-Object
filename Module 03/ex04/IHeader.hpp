#pragma once

#include <string>
#include <ctime>

class IHeader {
public:
    IHeader() = default;
    virtual ~IHeader() = default;
    virtual std::string getHeader() = 0;
};

class StringHeader : public IHeader {
private:
    std::string header;
public:
    StringHeader(const std::string& header) {
        this->header = header;
    }

    std::string getHeader() override {
        return header;
    }
};

class DateHeader : public IHeader {
public:
    std::string getHeader() override {
        time_t now = time(0);
        char buffer[80];
        struct tm tstruct;
        tstruct = *localtime(&now);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &tstruct);
        return buffer;
    }
};