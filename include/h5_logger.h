#ifndef H5_LOGGER_H_
#define H5_LOGGER_H_

#include <abstract_logger.h>
#include <string>

namespace Logger {
    class H5Manager;

    class H5Logger : public AbstractLogger<std::string, double> {
    public:
        H5Logger();
        ~H5Logger();
        
        // Should start a log, given a set of keys, and an optional
        // context for log names, etc
        //
        // Return true on success of the log start, false otherwise
        bool startLog(const std::vector<std::string>& keys, const std::string& path);

        // Should stop a log.
        bool stopLog();

        // Return true if the logger is currently logging
        bool isLogging();

        // Sets the decimation in Herz
        bool setDecimation(float decimationRateHz);

        // Logs some data with a key, value map
        bool log(const std::map<std::string, double>& data);

        // Logs some data with a value vector. Understood that the keys have
        // Been passed in previously in start log
        bool log(const std::vector<double>& data);

    private:
        H5Manager* manager;
    };
}

#endif