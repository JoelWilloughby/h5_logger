#ifndef BUFFERED_LOGGER_H_
#define BUFFERED_LOGGER_H_ value

#include <abstract_logger.h>
#include <string>

namespace Logger {

enum LoggerType {
    H5_LOGGER,
    LDF_LOGGER
};

typedef AbstractLogger<std::string, double> NormalLogger;

NormalLogger * CreateLogger(LoggerType loggerType);

}

#endif