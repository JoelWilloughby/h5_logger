#ifndef H5_LOGGER_H_
#define H5_LOGGER_H_

#include <abstract_logger.h>
#include <string>

namespace Logger {
    typedef AbstractLogger<std::string, double> NormalLogger;

    NormalLogger* CreateLogger();
}

#endif