#include "FileLogger.hpp"
#include "OStreamLogger.hpp"

int main () {
    FileLogger fileLogger("log.txt");
    OStreamLogger ostreamLogger(std::cout);

    fileLogger.write("Hello, Filewriteger!");
    ostreamLogger.write("Hello, OStreamLogger!");

    return 0;
}