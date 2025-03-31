#include "ILogger.hpp"
#include "IHeader.hpp"
#include <vector>

int main () {
    std::vector<ILogger*> loggers = {
        new OStreamLogger(std::cout),
        new OStreamLogger(std::cout, new StringHeader("Error")),
        new OStreamLogger(std::cout, new DateHeader()),
        new FileLogger("log.txt"),
        new FileLogger("log.txt", new StringHeader("Error")),
        new FileLogger("log.txt", new DateHeader())
    };

    for (const auto& logger : loggers) {
        logger->write("This is a log message.");
    }

    for (const auto& logger : loggers) {
        delete logger;
    }

    return 0;
}